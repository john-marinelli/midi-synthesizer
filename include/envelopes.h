#include "globalvalues.h"
#include <Arduino.h>

float volumeEnvelope(bool envIsPlaying, bool &envBang, bool &envOffBang, elapsedMillis &envElapsedTime, float &marker);