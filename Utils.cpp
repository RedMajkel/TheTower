#include "Utils.h"

std::string IntToStr(int number) {
	std::stringstream ss;
	ss << number;
	return ss.str();
}

float NRand()
{
	static int q = 15;
	static float c1 = (1 << q) - 1;
	static float c2 = ((int)(c1 / 3)) + 1;
	static float c3 = 1.f / c1;
	/* random number in range 0 - 1 not including 1 */
	float random = 0.f;

	/* the white noise */
	float noise = 0.f;
	random = ((float)(rand()) / (float)(RAND_MAX + 1));
	random = (2.f * ((random * c2) + (random * c2) + (random * c2)) - 3.f * (c2 - 1.f)) * c3;
	return random;
}