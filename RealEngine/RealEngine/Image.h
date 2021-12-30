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
	// 通道数量
	int nrChannel;

	// 世界变换矩阵
	Matrix4* uWorldTransform;

	unsigned char* m_pData;

	unsigned int mTextureID;
	// 加载纹理数据
	void loadTexture();
	void unloadTexture();

	// 绑定顶点数组
	void bindVertexArray();
private:
	void loadFromMemoryTest(std::string filename);
public:
	// 调用绘制
	void draw();

public:
	void SetPosition(float x, float y, float z);
	void SetScale(float scaleX, float scaleY, float scaleZ);
	void SetRotation(float angle);
};