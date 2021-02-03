#include "OpenglDriver.h"

RealEngine::OpenglDriver::OpenglDriver() 
{

}

RealEngine::OpenglDriver::~OpenglDriver() 
{

}

void RealEngine::OpenglDriver::drawTriangle()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f
	};

	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}