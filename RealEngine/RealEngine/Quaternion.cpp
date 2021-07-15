#include <cmath>

#include "Quaternion.h"
#include "Math.h"

Quaternion::Quaternion(float inX, float inY, float inZ, float inW)
{
	x = inX;
	y = inY;
	z = inZ;
	w = inW;
}

Quaternion::Quaternion(Vector3f& axis, float angle)
{
	float scalar = sinf(angle / 2.0f);
	x = axis.x * scalar;
	y = axis.y * scalar;
	z = axis.z * scalar;
	w = cosf(angle / 2.0f);
}