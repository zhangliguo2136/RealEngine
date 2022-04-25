#include "Math.h"

#include "Vector.h"

float Math::radians(float angle)
{
	return angle * 3.1415926f / 180;
}


float Math::random_float()
{
	float res;
	unsigned int tmp;
	static unsigned int seed = 0xFFFF0C59;

	seed *= 16807;

	tmp = seed ^ (seed >> 4) ^ (seed << 15);

	*((unsigned int *)&res) = (tmp >> 9) | 0x3F800000;

	return (res - 1.0f);
}

Vector3f Math::random_vector(float minmag, float maxmag)
{
	Vector3f randomvec(random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f);
	randomvec = Vector3f::normalize(randomvec);

	randomvec = randomvec * (random_float() * (maxmag - minmag) + minmag);
	return randomvec;
}

