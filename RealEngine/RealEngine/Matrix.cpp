#include "Matrix.h"

Matrix4::Matrix4() 
{

}
Matrix4::~Matrix4() 
{

}
float* Matrix4::getMatrixData()
{
	return data;
}

Matrix4 Matrix4::operator*(const Matrix4 &mat4) const
{
	// TODO æÿ’Û≥À∑®
	return mat4;
}

Vector4f Matrix4::operator*(const Vector4f &vec4) const
{
	return vec4;
}