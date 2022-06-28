#include "midihandle.h"

float midiToFreq(byte note) {
	float result = 0;
	float exp = ((note-69) / 12.0);
	result = 440.0 * (pow(2, exp)); 

	return result;
}

float normalizeControl(byte value) {
	return (value/127.0);
}

