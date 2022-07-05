#ifndef GLOBALVALUES
#define GLOBALVALUES

/* Global values used between functions defined in headers and the main.cpp file 
   Ideally, this header will not exist in the future in favor of an object-oriented
   approach */

static float normalVelocity = 0;

static float globalFreq = 440;

static float attackEnd = 50.0; // time after noteOn that attack ends

static float releaseEnd = 50.0; // time after noteOff signal that volume goes to 0

static float pitchAttackEnd = 100.0;

static float pitchReleaseEnd = 300.0;

static float pitchPeak = 500.0;

#endif