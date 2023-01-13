#include "RenderPathTracingCmd.h"

#include "GLShaderCache.h"
#include "RealEngine.h"

RenderPathTracingCmd::RenderPathTracingCmd()
{
	float vertices[] = {
			 1.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

RenderPathTracingCmd::~RenderPathTracingCmd()
{

}

void RenderPathTracingCmd::execute()
{
	auto glProgram = GLShaderCache::getInstance().findOrCreate("PathTracing");
	glProgram->UseProgram();

	EConfig config;

	Vector2f ScreenSize = Vector2f(config.Width, config.Height);
	glProgram->setUniform2fv("screenSize", ScreenSize.values);

	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}