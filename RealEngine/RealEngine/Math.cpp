#include "Math.h"
#include "Matrix.h"
Vector2f::Vector2f(float x, float y)
	:x(x), y(y)
{
}



Vector3f::Vector3f(float x, float y, float z)
	:x(x), y(y), z(z)
{
}



Vector4f::Vector4f(float x, float y, float z, float w)
	:x(x), y(y), z(z), w(w)
{
}

Vector4f Vector4f::operator*(Matrix4 &mat) const 
{
	float* otherData = mat.GetMatrixData();
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