#ifndef PITCHENVELOPES
#define PITCHENVELOPES

/* This header defines all envelope functions that attenuate signals over time. */

#include "globalvalues.h"
#include <Arduino.h>

//A simple ASR (when accounting for overall volume or velocity) envelope, with variable attack and release.
float pitchEnvelope(bool envIsPlaying, bool &envBang, bool &envOffBang, elapsedMillis &envElapsedTime, float &marker);

//TODO -- implement AR envelope with zero sustain (for drum sounds)

#endif