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
			result = pow(((marker * (envElapsedTime / releaseEnd)) + 1), -10); //-10 seems like a good value, but can be changed
		}
		else {
			result = 0.0;
		}
	}

	return result;
}