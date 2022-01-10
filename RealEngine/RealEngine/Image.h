#pragma once
#include <string>
#include "Matrix.h"
#include "Vector.h"


class Image
{
public:
	Image(std::string filename);
	~Image();

	virtual void draw();

	void loadFromFile(std::string filename);

	static unsigned int BindTexture(std::string filename);
private:
	int height;
	int width;
	// ͨ������
	int nrChannel;

	// ģ�ͱ任����
	Matrix4 _model;

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
	void SetPosition(float x, float y, float z);
	void SetScale(float scaleX, float scaleY, float scaleZ);
	void SetRotation(float angle);
};