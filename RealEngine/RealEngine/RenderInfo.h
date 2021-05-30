#pragma once

class RenderInfo
{
public:
	RenderInfo(float *vertices, size_t count);
public:
	// 顶点数组
	float *verticeArray;
	// 顶点数组的大小
	size_t arraySize;
};