#pragma once
#include "Shader.h"

class RenderInfo
{
public:
	RenderInfo(float *vertices, size_t count);
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
	Shader* _shader;
	void useGLProgram();
};