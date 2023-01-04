#pragma once

#include "Particle.h"

class ParticleScene
{
public:
	ParticleScene();
	~ParticleScene();

	void update(float deltaTime);

private:
	
	Particle* _particle = nullptr;
};