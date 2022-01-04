#include "Vector.h"
#include "Matrix.h"

#include <math.h>

Vector2f::Vector2f(float x, float y)
	:x(x), y(y)
{
}

Vector2d::Vector2d(double x, double y)
	: x(x), y(y)
{
}

Vector3f::Vector3f(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

Vector3f Vector3f::operator-(const Vector3f &vec1) const
{
	return Vector3f(x - vec1.x, y - vec1.y, z - vec1.z);
}

Vector3f Vector3f::operator+(const Vector3f &vec1) const
{
	return Vector3f(x + vec1.x, y + vec1.y, z + vec1.z);
}

Vector3f Vector3f::operator*(const float& value) const
{
	return Vector3f(value * x, value * y, value * z);
}

Vector3f Vector3f::normalize(const Vector3f& vec1)
{
	float len = sqrt(vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z);
	Vector3f vec(vec1.x / len, vec1.y / len, vec1.z / len);
	return vec;
}
Vector3f Vector3f::cross(const Vector3f &vec1, const Vector3f &vec2)
{
	Vector3f vec;

	vec.x = vec1.y * vec2.z - vec2.y * vec1.z;
	vec.y = vec2.x * vec1.z - vec1.x * vec2.z;
	vec.z = vec1.x * vec2.y - vec2.x * vec1.y;

	return vec;
}
Vector3f Vector3f::dot(const Vector3f &, const Vector3f &)
{
	return Vector3f(0.0f, 0.0f, 0.0f);
}



Vector4f::Vector4f(float x, float y, float z, float w)
	:x(x), y(y), z(z), w(w)
{
}

Vector4f Vector4f::operator*(Matrix4 &mat) const
{
	float* otherData = mat.data();
	float data[4] = { x, y, z, w };
	float newData[4] = { 0 };

	for (int col = 0; col < 4; ++col)
	{
		for (int k = 0; k < 4; ++k)
		{
			newData[col] += data[k] * otherData[k * 4 + col];
		}
	}

	Vector4f vec4;
	vec4.x = newData[0];
	vec4.y = newData[1];
	vec4.z = newData[2];
	vec4.w = newData[3];
	return vec4;
}