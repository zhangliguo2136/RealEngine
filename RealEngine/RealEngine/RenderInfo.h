#pragma once
#include "Shader.h"

class RenderInfo
{
public:
	RenderInfo(float *vertices, size_t count);

	~RenderInfo() {};
public:
	// ��������
	float *verticeArray;
	// ��������Ĵ�С
	size_t arraySize;

	// ���������
	int count;
	// ��״
	int shape;
};