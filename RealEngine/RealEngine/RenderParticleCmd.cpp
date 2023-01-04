#include "RenderParticleCmd.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "GLShaderCache.h"

RenderParticleCmd::RenderParticleCmd()
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	GLfloat particle_quad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	unsigned vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	/*
	ÏêÇé²é¿´LearnOpenGL
	*/
	//glGenBuffers(1, &_positionBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, _positionBuffer);
	//glBufferData(GL_ARRAY_BUFFER, _particleCount * sizeof(Vector4f), NULL, GL_DYNAMIC_COPY);

	//Vector4f* positions = (Vector4f*)glMapBufferRange(GL_ARRAY_BUFFER, 0, _particleCount * sizeof(Vector4f), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	//for (int i = 0; i < _particleCount; ++i)
	//{
	//	positions[i].x = _particles[i].Position.x;
	//	positions[i].y = _particles[i].Position.y;
	//	positions[i].z = _particles[i].Position.z;
	//	positions[i].w = _particles[i].Color.w;
	//}

	//glUnmapBuffer(GL_ARRAY_BUFFER);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindVertexArray(0);
}

RenderParticleCmd::~RenderParticleCmd()
{

}


void RenderParticleCmd::execute()
{
	auto shader = GLShaderCache::getInstance().findOrCreate("ParticlePoint_Test");
	shader->UseProgram();

	glBindTexture(GL_TEXTURE_2D, ParticleTextureID);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBindVertexArray(_vao);

	//Vector4f* positions = (Vector4f*)glMapBufferRange(GL_ARRAY_BUFFER, 0, _particleCount * sizeof(Vector4f), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	//for (int i = 0; i < _particleCount; ++i)
	//{
	//	positions[i].x = _particles[i].Position.x;
	//	positions[i].y = _particles[i].Position.y;
	//	positions[i].z = _particles[i].Position.z;
	//	positions[i].w = _particles[i].Color.w;
	//}

	//glUnmapBuffer(GL_ARRAY_BUFFER);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, ParticleCount);

	glBindVertexArray(0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}