#pragma once
//#include "Matrix.h"

class Matrix4;

class Vector3f
{
public:
	Vector3f() {};
	~Vector3f() {};
public:
	Vector3f(float x, float y, float z);

public:
	float x, y, z;
};

class Vector4f 
{
public:
	Vector4f() {};
	~Vector4f() {};
public:
	Vector4f(float x, float y, float z, float w);

	//重载向量与矩阵的乘法
	Vector4f operator*(Matrix4 &mat) const;

public:
	float x, y, z, w;
};

