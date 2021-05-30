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

void RealEngine::OpenglDriver::drawTriangle()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int vao, vbo;

	/*创建顶点数组对象
	*/
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	/* 创建Buffer
	void glGenBuffer(GLsizei n, GLuint* buffers)
	返回n 个当前未使用的缓存对象名称，并保存到buffers数组中
	*/
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glClear(GL_COLOR_BUFFER_BIT);

	Shader shader("../Resource/shader/common.vert", "../Resource/shader/common.frag");

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void RealEngine::OpenglDriver::loadShaderTest()
{
	//GLuint shaderID = loadShaders("../shader/common.vert", "../shader/common.frag");

	//printf("OpenglDriver::loadShaderTest_______shaderID is %d\n", shaderID);
}

void RealEngine::OpenglDriver::draw(RenderInfo renderInfo)
{

}