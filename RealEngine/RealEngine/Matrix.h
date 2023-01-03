#pragma once
#include <iostream>

#include "Vector.h"
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

	void Dump();
public:
	static Matrix4 IdentityMatrix();

	static Matrix4 Perspective(float fov, float aspect, float n, float f);

	static Matrix4 RotationByQuat(const Quaternion& quat);
	static Matrix4 Rotation(const Vector3f& vec3);
	static Matrix4 Translate(const Vector3f& vec3);
	static Matrix4 Scale(const Vector3f& vec3);

public:
	float* data();
private:
	float _values[16];
};