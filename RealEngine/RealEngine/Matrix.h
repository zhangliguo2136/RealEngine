#pragma once

#include "Math.h"
#include "Quaternion.h"

class Matrix4
{
public:
	Matrix4();
	~Matrix4();

	// 单位矩阵
	void Identity();

	// 重载矩阵乘法
	Matrix4 operator*(Matrix4 &) const;

	float* data();

	void copyForm(Matrix4 &);

public:
	static Matrix4 IdentityMatrix();

	static Matrix4 Perspective(float fov, float aspect, float n, float f);

	static Matrix4 CreateRotationMatrix(Quaternion& quat);
	static Matrix4 CreateMoveMatrix(Vector3f vec3);
	static Matrix4 CreateScaleMatrix(Vector3f vec3);

private:
	float _values[16];
};