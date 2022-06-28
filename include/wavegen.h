#ifndef WAVEGEN
#define WAVEGEN

/* Header for all wave-generating functions.
   In the future this will include a wavetable
   sin function, square wave and noise functions. */

#include <Arduino.h>
#include <Audio.h>

//Simple square wave generator that switches between -8000 and 8000
//based on phase
int16_t nextSquareSample(float freq);

#endif