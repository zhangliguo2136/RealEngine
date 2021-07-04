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
float* Matrix4::getMatrixData()
{
	return data;
}

Matrix4 Matrix4::operator*(Matrix4 &mat4) const
{
	Matrix4 mat;
	float* newData = mat.getMatrixData();
	float* otherData = mat4.getMatrixData();

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

void Matrix4::IdentityMatrix() 
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