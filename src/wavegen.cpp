#include "wavegen.h"

int16_t nextSquareSample(float freq) {
	static float squarePhase = 0.f;
	int16_t result = 0;

	if (squarePhase > PI) {
		result = 8000;
	}
	else {
		result = -8000;
	}
	
	squarePhase += freq/AUDIO_SAMPLE_RATE_EXACT*TWO_PI;
	if (squarePhase >= TWO_PI) {
		squarePhase -= TWO_PI;
	}

	return result;
}