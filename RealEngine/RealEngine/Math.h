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
	union
	{
		float values[2];
		struct
		{
			float x, y;
		};
	};
};


class Vector3f
{
public:
	Vector3f() {};
	~Vector3f() {};
public:
	Vector3f(float x, float y, float z);

public:
	union 
	{
		float values[3];
		struct 
		{
			float x, y, z;
		};
	};
};

class Vector3i
{
public:
	Vector3i() {};
	~Vector3i() {};
public:
	Vector3i(int x, int y, int z) {};

public:
	union
	{
		int values[3];
		struct
		{
			int x, y, z;
		};
	};
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

