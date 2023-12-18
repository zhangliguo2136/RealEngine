#pragma once

class Matrix4;

class Vector2i
{
public:
	Vector2i() {};
	~Vector2i() {};
public:
	Vector2i(int x, int y);

public:
	union
	{
		int values[2];
		struct
		{
			int x, y;
		};
	};
};

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

class Vector2d
{
public:
	Vector2d() {};
	~Vector2d() {};
public:
	Vector2d(double x, double y);

public:
	union
	{
		double values[2];
		struct
		{
			double x, y;
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

	Vector3f operator-(const Vector3f &) const;
	Vector3f operator+(const Vector3f &) const;

	Vector3f operator*(const float&) const;

	static Vector3f normalize(const Vector3f &);
	static Vector3f cross(const Vector3f &, const Vector3f &);
	static float dot(const Vector3f &, const Vector3f &);
public:
	union
	{
		float values[3];
		struct
		{
			float x, y, z;
		};
	};

public:
	// Constants
	static const Vector3f Zero;
	static const Vector3f One;
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
public:
	union
	{
		float values[4];
		struct
		{
			float x, y, z, w;
		};
	};
};


typedef Vector2f TVector2f;
typedef Vector2i TVector2i;
typedef Vector2d TVector2d;

typedef Vector3f TVector3f;
typedef Vector3i TVector3i;

typedef Vector4f TVector4f;