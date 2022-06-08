#include "OpenglDriver.h"

#include <iostream>
#include "Shader.h"
#include "ShaderLoader.h"

RealEngine::OpenglDriver::OpenglDriver() 
{

}

RealEngine::OpenglDriver::~OpenglDriver() 
{

}

void RealEngine::OpenglDriver::render(RenderInfo& renderInfo)
{
	float* verticeArray = renderInfo.verticeArray;

	glDrawArrays(renderInfo.shape, 0, renderInfo.count);
}