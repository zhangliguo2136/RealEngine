#include "ParticleSystem.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <sstream>

#include "Image.h"
#include "Math.h"

ParticleSystem::ParticleSystem() 
{
	for (auto i = 0; i < _particleCount; ++i)
	{
		Particle particle;
		particle.Life = Math::random_float();
		particle.Position = Math::random_vector();
		particle.Velocity = Math::random_vector();

		_particles.push_back(particle);
	}

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

	_textureID = Image::BindTexture("../Resource/images/particle.png");

	_shader = new Shader(
		"../Resource/shaders/ParticlePoint_Test.vs", 
		"../Resource/shaders/ParticlePoint_Test.fs"
		);
}

ParticleSystem::~ParticleSystem() 
{

}

void ParticleSystem::update(float deltaTime)
{
	for (auto i = 0; i < _particles.size(); ++i)
	{
		Particle &p = _particles[i];

		p.Life -= deltaTime;

		if (p.Life > 0.0f)
		{
			p.Position = p.Position - p.Velocity * deltaTime;
			p.Color.w = p.Color.w - deltaTime * 0.25;
		}
		else
		{
			p.Life = Math::random_float();
			p.Color.w = 1.0f;
			p.Position = Math::random_vector();
		}
	}

	_shader->useProgram();
	glBindTexture(GL_TEXTURE_2D, _textureID);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBindVertexArray(_vao);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, _particleCount);

	glBindVertexArray(0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}