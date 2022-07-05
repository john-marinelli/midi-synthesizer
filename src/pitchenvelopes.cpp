#include "pitchenvelopes.h"

float pitchEnvelope(bool envIsPlaying, bool &envOnBang, bool &envOffBang, elapsedMillis &envElapsedTime, float &marker) {

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
		if (envElapsedTime <= pitchAttackEnd) {
			result = envElapsedTime / pitchAttackEnd;
			marker = result;
		}
		else {
			result = 1.0;
			marker = result;
		}
	}
	else {
		if (envElapsedTime <= pitchReleaseEnd) {
			result = pow(((marker * (envElapsedTime / pitchReleaseEnd)) + 1), -10); //-10 seems like a good value, but can be changed
		}
		else {
			result = 0.0;
		}
	}

	return result;
}