#ifndef MIDIHANDLE
#define MIDIHANDLE

#include <Arduino.h>
#include "globalvalues.h"

//converts midi note number to frequency andreturns float
//Possibly replace with table? Depends on comp cost
float midiToFreq(byte note);

//normalizes 127 scale control message between 0 and 1
//also used for velocity
float normalizeControl(byte velocity);

//handles incoming control change message
void onControlChange(byte channel, byte control, byte value);

#endif