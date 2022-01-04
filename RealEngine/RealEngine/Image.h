#pragma once
#include <string>
#include "IBaseObject.h"
#include "Matrix.h"
#include "Vector.h"

using namespace RealEngine;

class Image : public IBaseObject
{
public:
	Image(std::string filename);
	~Image();

	virtual void draw() override;
	virtual void update(float deltaTime) override {} ;
	virtual void onEnter() override {};
	virtual void onExit() override {};
	virtual void updateTransform(Matrix4 view, Matrix4 projection) override {};

	void loadFromFile(std::string filename);

	static unsigned int BindTexture(std::string filename);
private:
	int height;
	int width;
	// 通道数量
	int nrChannel;

	// 模型变换矩阵
	Matrix4 _model;

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
	void SetPosition(float x, float y, float z);
	void SetScale(float scaleX, float scaleY, float scaleZ);
	void SetRotation(float angle);
};