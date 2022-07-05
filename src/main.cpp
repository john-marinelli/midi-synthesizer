#include "midihandle.h"
#include "wavegen.h"
#include "envelopes.h"
#include "onepolefilter.h"
#include "pitchenvelopes.h"

//Audio routing -- this uses an AudioPlayQueue object
//that allows for feeding raw samples to the audio shield.
AudioPlayQueue           audio;         
AudioOutputI2S           i2s1;           
AudioConnection          patchCord1(audio, 0, i2s1, 0);
AudioConnection          patchCord2(audio, 0, i2s1, 1);
AudioControlSGTL5000     control;

elapsedMillis globalEnvTime;
elapsedMillis pitchGlobalEnvTime;
//For keeping track of note on message
//Set in midi callbacks
bool isPlaying = false;
//Not currently used, but will be to 
//switch between envelopes
bool isSustain = true;
//Bang messages for kicking off envelopes
bool globalOffBang = false;
bool globalOnBang = false;

bool pitchGlobalOnBang = false;
bool pitchGlobalOffBang = false;
//Intermediate value for calculating envelope
//on a per-buffer basis (cuts down on computation)
float envValue = 0.0;
//Used in order to switch gracefully into a release
//if an attack is not yet over
float lastEnvValue = 0.0;

float pitchEnvValue = 0.0;

float pitchLastEnvValue = 0.0;

int16_t tempSample = 0;

//For storing Midi CC messages
float normalControl0 = 10000;
float normalControl1 = 0;

int debugval = 0;

OnePole *onePoleFilter = new OnePole();

/*------------------------------------------------------*/
//Midi callbacks used to be in headers, but values weren't responding.

void onNoteOn(byte channel, byte note, byte velocity) {
	globalFreq = midiToFreq(note);
	normalVelocity = normalizeControl(velocity);
	isPlaying = true;
	globalOnBang = true;
	pitchGlobalOnBang = true;
}

void onNoteOff(byte channel, byte note, byte velocity) {
	isPlaying = false;
	globalOffBang = true;
	pitchGlobalOffBang = true;
}

void onControlChange(byte channel, byte control, byte value) {
	
	//can be extended to other messages -- if so globals 
	//need to be added in main to accomodate
	switch(control) {
		case 1:
			normalControl0 = normalizeControl(value);
			normalControl0 = normalControl0 * 1000.0;
		case 2:
			normalControl1 = normalizeControl(value);
	}

}

/*----------------------------------------------------------*/

void setup() {
	//Initialize midi and debugging serial connection
	Serial.begin(9600);
	usbMIDI.setHandleNoteOff(onNoteOff);
	usbMIDI.setHandleNoteOn(onNoteOn);
	usbMIDI.setHandleControlChange(onControlChange);
	//Allocate audio memory and set audio shield's volume
	AudioMemory(20);
	control.enable();
	control.volume(0.5);
	//TODO -- investigate different buffer sizes
	audio.setMaxBuffers(10);
}

void loop() {

	usbMIDI.read();
	//Set envelope once per buffer
	envValue = volumeEnvelope(isPlaying, globalOnBang, globalOffBang, globalEnvTime, lastEnvValue);

	pitchEnvValue = pitchEnvelope(isPlaying, pitchGlobalOnBang, pitchGlobalOffBang, pitchGlobalEnvTime, pitchLastEnvValue);

	if (pitchEnvValue > 0.01) {
		Serial.println(pitchEnvValue);
	}

	//Set coefficients once per buffer
	onePoleFilter->setFc(normalControl0 / AUDIO_SAMPLE_RATE_EXACT); 

	int16_t* buffer = audio.getBuffer();

	for (byte i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
		tempSample = nextSquareSample(globalFreq + (pitchPeak * (1.0-pitchEnvValue))) * envValue;
		buffer[i] = tempSample - onePoleFilter->process(tempSample);
	}

	audio.playBuffer();

}