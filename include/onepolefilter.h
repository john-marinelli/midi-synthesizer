#ifndef ONEPOLEFILTER
#define ONEPOLEFILTER

/* Simple (and not very sonically pleasing) single-pole filter.
   In the future, this will be extended or a new class will be
   created for a better, resonant lowpass filter */

#include <Arduino.h>
#include <Audio.h>
#include "globalvalues.h"
#include "math.h"

class OnePole {
public:
	OnePole() {a0 = 1.0; b1 = 0.0; z1 = 0.0;};
	OnePole(double Fc) {z1 = 0.0; setFc(Fc);};
	~OnePole();

	void setFc(double Fc);
	int16_t process(int16_t in);

protected:
	double a0;
	double b1;
	double z1;
};

//Sets filter coefficients
inline void OnePole::setFc(double Fc) {
	b1 = exp(-2.0 * PI * Fc);
	a0 = 1.0 - b1;
}

//Process per-sample 
inline int16_t OnePole::process(int16_t in) {
	return (int16_t)(z1 = in * a0 + z1 * b1);
}

#endif