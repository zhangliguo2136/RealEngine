#pragma once
//#include "Matrix.h"

class Matrix4;

class Vector2f
{
public:
	Vector2f() {};
	~Vector2f() {};
public:
	Vector2f(float x, float y);

public:
	float x, y;
};


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

	//�������������ĳ˷�
	Vector4f operator*(Matrix4 &mat) const;

public:
	float x, y, z, w;
};

class Size
{
public:
	Size() {};
	~Size() {};
public:
	Size(float inWidth, float inHeight) 
	{
		width = inWidth;
		height = inHeight;
	}
public:
	float width, height;
};

