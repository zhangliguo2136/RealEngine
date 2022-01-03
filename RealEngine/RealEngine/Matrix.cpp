#include "Matrix.h"
#include <math.h>

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

Matrix4 Matrix4::operator*(Matrix4 &mat4) const
{
	Matrix4 mat;
	float* newValues = mat.data();
	float* otherValues = mat4.data();

	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			int index = row * 4 + col;

			for (int k = 0; k < 4; ++k)
			{
				newValues[index] += _values[row * 4 + k] * otherValues[k * 4 + col];
			}
		}
	}
	return mat;
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

Matrix4 Matrix4::CreateMoveMatrix(Vector3f vec3)
{
	Matrix4 mat = Matrix4::IdentityMatrix();
	float* matData = mat.data();

	matData[12] = vec3.x;
	matData[13] = vec3.y;
	matData[14] = vec3.z;

	return mat;
}
Matrix4 Matrix4::CreateScaleMatrix(Vector3f vec3)
{
	Matrix4 mat = Matrix4::IdentityMatrix();
	float* matData = mat.data();
	matData[0] += vec3.x;
	matData[5] += vec3.y;
	matData[10] += vec3.z;

	return mat;
}

Matrix4 Matrix4::CreateRotationMatrix(Quaternion& quat)
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

void Matrix4::copyForm(Matrix4 &mat4)
{
	float* inValues = mat4.data();

	for (int i = 0; i < 16; ++i)
	{
		_values[i] = inValues[i];
	}
}

Matrix4 Matrix4::Perspective(float fov, float aspect, float n, float f)
{
	float q = 1.0f / tan(fov / 3.1415 * 180);

	float A = q / aspect;
	float B = (n + f) / (n - f);
	float C = (2.0f * n * f) / (n - f);

	Matrix4 mat;
	float* values = mat.data();
	values[0] = A;
	values[5] = q;
	values[10] = B;
	values[11] = -1;
	values[14] = C;

	return mat;
}