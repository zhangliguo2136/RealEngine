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
	// ��������
	float *verticeArray;
	// ��������Ĵ�С
	size_t arraySize;

	// ���������
	int count;
	// ��״
	int shape;
public:
	void useGLProgram();

private:
	Shader* _shader = nullptr;
};