#pragma once
#include "BaseObject.h"

class SceneObjectTransfrom :public BaseObject
{
public:
	/*
	通常是一个4x4 矩阵
	*/
	float mat4[16];
};