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

void RealEngine::OpenglDriver::draw(RenderInfo& renderInfo)
{
	float* verticeArray = renderInfo.verticeArray;
	renderInfo.useGLProgram();

	glDrawArrays(renderInfo.shape, 0, renderInfo.count);
}