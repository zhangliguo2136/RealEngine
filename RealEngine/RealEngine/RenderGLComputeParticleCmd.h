#pragma once

#include "RenderCommand.h"
#include <vector>

#include "GLShaderCache.h"

class RenderGLComputeParticleCmd :public RenderCommand
{
public:
	virtual void execute() override;

public:
	RenderGLComputeParticleCmd();
	~RenderGLComputeParticleCmd();

public:
	void update(float deltaTime);

public:
	int ParticleCount = 0;

private:
	const int PARTICLE_GROUP_SIZE = 1024;
	const int PARTICLE_GROUP_COUNT = 8192;
	const int PARTICLE_COUNT = (PARTICLE_GROUP_SIZE * PARTICLE_GROUP_COUNT);
	const int MAX_ATTRACTORS = 64;

	// Posisition and velocity buffers
	union
	{
		struct
		{
			GLuint position_buffer;
			GLuint velocity_buffer;
		};
		GLuint buffers[2];
	};

	// TBOs
	union
	{
		struct
		{
			GLuint position_tbo;
			GLuint velocity_tbo;
		};
		GLuint tbos[2];
	};

	// Attractor UBO
	GLuint  attractor_buffer;

	// Program, vao and vbo to render a full screen quad
	GLuint  render_prog;
	GLuint  render_vao;
	GLuint  render_vbo;

	// Mass of the attractors
	float attractor_masses[64];
};
