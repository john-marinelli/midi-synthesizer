#include "envelopes.h"

float volumeEnvelope(bool envIsPlaying, bool &envOnBang, bool &envOffBang, elapsedMillis &envElapsedTime, float &marker) {

	float result = 0;

	if (envOnBang) {
		envElapsedTime = 0;
		envOnBang = false;
	}
	else if (envOffBang) {
		envElapsedTime = 0;
		envOffBang = false;
	}

	if (envIsPlaying) {
		if (envElapsedTime <= attackEnd) {
			result = envElapsedTime / attackEnd;
			marker = result;
		}
		else {
			result = 1.0;
			marker = result;
		}
	}
	else {
		if (envElapsedTime <= releaseEnd) {
			result = pow(((marker * (envElapsedTime / releaseEnd)) + 1), -10); // the value -8 has to rise and fall in tandem with the length of the release tail
		}
		else {
			result = 0.0;
		}
	}

	return result;
}