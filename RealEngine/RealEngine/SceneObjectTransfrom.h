#pragma once
#include "BaseSceneObject.h"

class SceneObjectTransfrom :public BaseSceneObject
{
public:
	/*
	通常是一个4x4 矩阵
	*/
	float mat4[16];
};