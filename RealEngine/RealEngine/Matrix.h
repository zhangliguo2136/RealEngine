#pragma once

#include "math.h"
class Matrix4
{
public:
	Matrix4();
	~Matrix4();

	void IdentityMatrix();

	// ÖØÔØ¾ØÕó³Ë·¨
	Matrix4 operator*(Matrix4 &) const;

	float* getMatrixData();
private:
	float data[16];
};