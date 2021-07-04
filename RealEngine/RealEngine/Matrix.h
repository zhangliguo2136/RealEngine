#pragma once

#include "math.h"
class Matrix4
{
public:
	Matrix4();
	~Matrix4();

	// 单位矩阵
	void IdentityMatrix();

	// 平移矩阵
	void MoveMatrix(Vector3f vec3);
	// 缩放矩阵
	void ScaleMatrix(Vector3f vec3);

	// 重载矩阵乘法
	Matrix4 operator*(Matrix4 &) const;

	float* getMatrixData();
private:
	float data[16];
};