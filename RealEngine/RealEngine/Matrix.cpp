#include "Matrix.h"

Matrix4::Matrix4() 
{
	for (int i = 0; i < 16; ++i)
	{
		data[i] = 0;
	}
}
Matrix4::~Matrix4() 
{

}
float* Matrix4::GetMatrixData()
{
	return data;
}

Matrix4 Matrix4::operator*(Matrix4 &mat4) const
{
	Matrix4 mat;
	float* newData = mat.GetMatrixData();
	float* otherData = mat4.GetMatrixData();

	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			int index = row * 4 + col;

			for (int k = 0; k < 4; ++k)
			{
				newData[index] += data[row*4 + k] * otherData[k*4 + col];
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
				data[i * 4 + j] = 1;
			}
		}
	}
}

void Matrix4::MoveMatrix(Vector3f vec3)
{
	data[12] += vec3.x;
	data[13] += vec3.y;
	data[14] += vec3.z;
}

void Matrix4::ScaleMatrix(Vector3f vec3) 
{
	data[0] += vec3.x;
	data[5] += vec3.y;
	data[10] += vec3.z;
}

Matrix4 Matrix4::CreateMoveMatrix(Vector3f vec3)
{
	Matrix4 mat;
	mat.Identity();
	float* matData = mat.GetMatrixData();

	matData[12] = vec3.x;
	matData[13] = vec3.y;
	matData[14] = vec3.z;

	return mat;
}
Matrix4 Matrix4::CreateScaleMatrix(Vector3f vec3)
{
	Matrix4 mat;
	mat.Identity();
	float* matData = mat.GetMatrixData();
	matData[0] += vec3.x;
	matData[5] += vec3.y;
	matData[10] += vec3.z;

	return mat;
}

Matrix4 Matrix4::CreateFromQuaternion(Quaternion& quat) 
{
	Matrix4 mat;
	float* data = mat.GetMatrixData();

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
	float* inData = mat4.GetMatrixData();

	for (int i = 0; i < 16; ++i)
	{
		data[i] = inData[i];
	}
}