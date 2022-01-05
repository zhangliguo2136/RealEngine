#include "Matrix.h"
#include <math.h>

#include "Math.h"

Matrix4::Matrix4() 
{
	for (int i = 0; i < 16; ++i)
	{
		_values[i] = 0;
	}
}
Matrix4::~Matrix4() 
{

}
float* Matrix4::data()
{
	return _values;
}

Matrix4 Matrix4::operator*(Matrix4 &inMat) const
{
	Matrix4 newMat;
	float* newValues = newMat.data();
	float* otherValues = inMat.data();

	newValues[0] = _values[0] * otherValues[0] + _values[1] * otherValues[4] + _values[2] * otherValues[8] + _values[3] * otherValues[12];
	newValues[1] = _values[0] * otherValues[1] + _values[1] * otherValues[5] + _values[2] * otherValues[9] + _values[3] * otherValues[13];
	newValues[2] = _values[0] * otherValues[2] + _values[1] * otherValues[6] + _values[2] * otherValues[10] + _values[3] * otherValues[14];
	newValues[3] = _values[0] * otherValues[3] + _values[1] * otherValues[7] + _values[2] * otherValues[11] + _values[3] * otherValues[15];

	newValues[4] = _values[4] * otherValues[0] + _values[5] * otherValues[4] + _values[6] * otherValues[8] + _values[7] * otherValues[12];
	newValues[5] = _values[4] * otherValues[1] + _values[5] * otherValues[5] + _values[6] * otherValues[9] + _values[7] * otherValues[13];
	newValues[6] = _values[4] * otherValues[2] + _values[5] * otherValues[6] + _values[6] * otherValues[10] + _values[7] * otherValues[14];
	newValues[7] = _values[4] * otherValues[3] + _values[5] * otherValues[7] + _values[6] * otherValues[11] + _values[7] * otherValues[15];

	newValues[8] = _values[8] * otherValues[0] + _values[9] * otherValues[4] + _values[10] * otherValues[8] + _values[11] * otherValues[12];
	newValues[9] = _values[8] * otherValues[1] + _values[9] * otherValues[5] + _values[10] * otherValues[9] + _values[11] * otherValues[13];
	newValues[10] = _values[8] * otherValues[2] + _values[9] * otherValues[6] + _values[10] * otherValues[10] + _values[11] * otherValues[14];
	newValues[11] = _values[8] * otherValues[3] + _values[9] * otherValues[7] + _values[10] * otherValues[11] + _values[11] * otherValues[15];

	newValues[12] = _values[12] * otherValues[0] + _values[13] * otherValues[4] + _values[14] * otherValues[8] + _values[15] * otherValues[12];
	newValues[13] = _values[12] * otherValues[1] + _values[13] * otherValues[5] + _values[14] * otherValues[9] + _values[15] * otherValues[13];
	newValues[14] = _values[12] * otherValues[2] + _values[13] * otherValues[6] + _values[14] * otherValues[10] + _values[15] * otherValues[14];
	newValues[15] = _values[12] * otherValues[3] + _values[13] * otherValues[7] + _values[14] * otherValues[11] + _values[15] * otherValues[15];

	return newMat;
}

void Matrix4::Identity()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == j)
			{
				_values[i * 4 + j] = 1;
			}
		}
	}
}

Matrix4 Matrix4::IdentityMatrix()
{
	Matrix4 mat;
	mat.Identity();
	return mat;
}

Matrix4 Matrix4::Translate(const Vector3f& vec3)
{
	Matrix4 mat = Matrix4::IdentityMatrix();
	float* matData = mat.data();

	matData[3] = vec3.x;
	matData[7] = vec3.y;
	matData[11] = vec3.z;

	return mat;
}
Matrix4 Matrix4::Scale(const Vector3f& vec3)
{
	Matrix4 mat = Matrix4::IdentityMatrix();
	float* matData = mat.data();
	matData[0] += vec3.x;
	matData[5] += vec3.y;
	matData[10] += vec3.z;

	return mat;
}

Matrix4 Matrix4::RotationByQuat(const Quaternion& quat)
{
	Matrix4 mat;
	float* data = mat.data();

	data[0] = 1.0f - 2.0f * quat.y * quat.y - 2.0f * quat.z * quat.z;
	data[1] = 2.0f * quat.x * quat.y + 2.0f * quat.w * quat.z;
	data[2] = 2.0f * quat.x * quat.z - 2.0f * quat.w * quat.y;
	data[3] = 0.0f;

	data[4] = 2.0f * quat.x * quat.y - 2.0f * quat.w * quat.z;
	data[5] = 1.0f - 2.0f * quat.x * quat.x - 2.0f * quat.z * quat.z;
	data[6] = 2.0f * quat.y * quat.z + 2.0f * quat.w * quat.x;
	data[7] = 0.0f;

	data[8] = 2.0f * quat.x * quat.z + 2.0f * quat.w * quat.y;
	data[9] = 2.0f * quat.y * quat.z - 2.0f * quat.w * quat.x;
	data[10] = 1.0f - 2.0f * quat.x * quat.x - 2.0f * quat.y * quat.y;
	data[11] = 0.0f;

	data[12] = 0.0f;
	data[13] = 0.0f;
	data[14] = 0.0f;
	data[15] = 1.0f;

	return mat;
}

Matrix4 Matrix4::Perspective(float fov, float aspect, float n, float f)
{
	float q = 1.0f / tan(Math::radians(fov));

	float A = q / aspect;
	float B = (n + f) / (n - f);
	float C = (2.0f * n * f) / (n - f);

	Matrix4 mat;
	float* values = mat.data();

	values[0] = A;
	values[5] = q;
	values[10] = B;
	values[11] = C;
	values[14] = -1;

	return mat;
}