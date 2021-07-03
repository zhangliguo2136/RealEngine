#pragma once

#include "math.h"

class Matrix4
{
public:
	Matrix4();
	~Matrix4();

	// 重载矩阵乘法
	Matrix4 operator*(const Matrix4 &) const;
	// 重载矩阵和向量的乘法
	Vector4f operator*(const Vector4f &) const;

	float* getMatrixData();
private:
	float data[16];
};