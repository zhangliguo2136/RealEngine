#include "RenderInfo.h"

RenderInfo::RenderInfo(float *vertices, size_t count)
{

}

void RenderInfo::useGLProgram()
{
	if (_shader != nullptr) 
	{
		_shader->useProgram();
	}
}