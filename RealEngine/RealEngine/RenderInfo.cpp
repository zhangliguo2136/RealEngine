#include "RenderInfo.h"

void RenderInfo::useGLProgram()
{
	if (_shader != nullptr) 
	{
		_shader->useProgram();
	}
}