#pragma once
#include "IBaseObject.h"

using namespace RealEngine;

class SceneObjectTransfrom :public IBaseObject
{
public:
	/*
	ͨ����һ��4x4 ����
	*/
	float mat4[16];
};