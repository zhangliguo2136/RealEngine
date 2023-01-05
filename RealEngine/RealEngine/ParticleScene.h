#pragma once

#include "Particle.h"
#include "GLComputeParticle.h"

class ParticleScene
{
public:
	ParticleScene();
	~ParticleScene();

	void update(float deltaTime);

private:
	
	GLComputeParticle* _particle = nullptr;
};