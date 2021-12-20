#pragma once
#include "Shader.h"

class RenderInfo
{
public:
	RenderInfo(float *vertices, size_t count);

	~RenderInfo() 
	{
		if (_shader)
		{
			delete _shader;
		}
	}
public:
	// 顶点数组
	float *verticeArray;
	// 顶点数组的大小
	size_t arraySize;

	// 顶点的数量
	int count;
	// 形状
	int shape;
public:
	void useGLProgram();

private:
	Shader* _shader = nullptr;
};