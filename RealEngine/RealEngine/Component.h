#pragma once
#include "Transform.h"

class TComponent
{
public:
	TComponent() {}
	virtual ~TComponent() {}

protected:
	TTransform WorldTransform;
};