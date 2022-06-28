#include "midihandle.h"
#include "wavegen.h"
#include "envelopes.h"
#include "onepolefilter.h"


AudioPlayQueue           audio;         
AudioOutputI2S           i2s1;           
AudioConnection          patchCord1(audio, 0, i2s1, 0);
AudioConnection          patchCord2(audio, 0, i2s1, 1);
AudioControlSGTL5000     control;

elapsedMillis globalEnvTime;
bool isPlaying = false;
bool isSustain = true;
bool globalOffBang = false;
bool globalOnBang = false;
float envValue = 0.0;
float lastEnvValue = 0.0;
int16_t tempSample = 0;
float filterFreq = 1000;

float normalControl0 = 10000;
float normalControl1 = 0;

OnePole *onePoleFilter = new OnePole();

void onNoteOn(byte channel, byte note, byte velocity) {
	globalFreq = midiToFreq(note);
	normalVelocity = normalizeControl(velocity);
	isPlaying = true;
	globalOnBang = true;
}

void onNoteOff(byte channel, byte note, byte velocity) {
	isPlaying = false;
	globalOffBang = true;
}

void onControlChange(byte channel, byte control, byte value) {
	
	//can be extended to other messages -- if so globals need to be  
	//added in globalvalues.h 
	switch(control) {
		case 1:
			normalControl0 = normalizeControl(value);
			normalControl0 = normalControl0 * 1000.0;
		case 2:
			normalControl1 = normalizeControl(value);
	}

}

void setup() {
	Serial.begin(9600);
	usbMIDI.setHandleNoteOff(onNoteOff);
	usbMIDI.setHandleNoteOn(onNoteOn);
	usbMIDI.setHandleControlChange(onControlChange);

	AudioMemory(20);
	control.enable();
	control.volume(0.5);

	audio.setMaxBuffers(10);
}

void loop() {

	usbMIDI.read();
	envValue = volumeEnvelope(isPlaying, globalOnBang, globalOffBang, globalEnvTime, lastEnvValue);

	Serial.println(normalControl0);

	onePoleFilter->setFc(normalControl0 / AUDIO_SAMPLE_RATE_EXACT);

	
	int16_t* buffer = audio.getBuffer();

	for (byte i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
		tempSample = nextSquareSample(globalFreq) * envValue;
		buffer[i] = onePoleFilter->process(tempSample);
	}

	// if (isPlaying == true) {
	// 	for (byte i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
	// 		buffer[i] = nextSquareSample(globalFreq);
	// 	}
	// }
	// else {
	// 	for (byte i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
	// 		buffer[i] = 0;
	// 	}
	// }

	audio.playBuffer();
}