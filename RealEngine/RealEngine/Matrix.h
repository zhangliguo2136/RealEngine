#pragma once

#include "math.h"
#include "Quaternion.h"

class Matrix4
{
public:
	Matrix4();
	~Matrix4();

	// ��λ����
	void Identity();

	// ƽ�ƾ���
	void MoveMatrix(Vector3f vec3);
	// ���ž���
	void ScaleMatrix(Vector3f vec3);

	// ���ؾ���˷�
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