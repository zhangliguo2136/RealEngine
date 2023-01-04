#pragma once

#include "GLProgram.h"

class GLComputeProgram :public GLProgram
{
public:
	virtual void Dispatch(int x = 1, int y = 1, int z = 1) override;
};