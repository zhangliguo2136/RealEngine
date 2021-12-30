#pragma once

#include "math.h"
#include "Quaternion.h"

class Matrix4
{
public:
	Matrix4();
	~Matrix4();

	// 单位矩阵
	void Identity();

	// 平移矩阵
	void MoveMatrix(Vector3f vec3);
	// 缩放矩阵
	void ScaleMatrix(Vector3f vec3);

	// 重载矩阵乘法
	Matrix4 operator*(Matrix4 &) const;

	float* GetMatrixData();

	void copyForm(Matrix4 &);

public:
	static Matrix4 CreateFromQuaternion(Quaternion& quat);
	static Matrix4 CreateMoveMatrix(Vector3f vec3);
	static Matrix4 CreateScaleMatrix(Vector3f vec3);
private:
	float data[16];
};