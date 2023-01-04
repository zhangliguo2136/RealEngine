#include "GLComputeProgram.h"

void GLComputeProgram::Dispatch(int x, int y, int z)
{
	glDispatchCompute(x, y, z);
}