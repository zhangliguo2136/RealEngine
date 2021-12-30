#pragma once
#include <string>
#include "IBaseObject.h"

class Matrix4;
class Vector3f;

using namespace RealEngine;

class Image : public IBaseObject
{
public:
	Image(std::string filename);
	~Image();

	void loadFromFile(std::string filename);
private:
	int height;
	int width;
	// ͨ������
	int nrChannel;

	// ����任����
	Matrix4* uWorldTransform;

	unsigned char* m_pData;

	unsigned int mTextureID;
	// ������������
	void loadTexture();
	void unloadTexture();

	// �󶨶�������
	void bindVertexArray();
private:
	void loadFromMemoryTest(std::string filename);
public:
	// ���û���
	void draw();

public:
	void SetPosition(float x, float y, float z);
	void SetScale(float scaleX, float scaleY, float scaleZ);
	void SetRotation(float angle);
};