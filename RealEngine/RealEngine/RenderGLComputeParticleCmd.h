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

	GLuint  render_vao;

	// Posisition and velocity buffers (vbo)
	union
	{
		struct
		{
			GLuint position_buffer;
			GLuint velocity_buffer;
		};
		GLuint buffers[2];
	};

	// TBOs (Texture Buffer)
	union
	{
		struct
		{
			GLuint position_tbo;
			GLuint velocity_tbo;
		};
		GLuint tbos[2];
	};

	// Attractor UBO (uniform buffer)
	GLuint  attractor_buffer;

	// Mass of the attractors
	float attractor_masses[64];
};
