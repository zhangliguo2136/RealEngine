#pragma once
#include "IBaseObject.h"

using namespace RealEngine;

class SceneObjectTransfrom :public IBaseObject
{
public:
	/*
	通常是一个4x4 矩阵
	*/
	float mat4[16];
};