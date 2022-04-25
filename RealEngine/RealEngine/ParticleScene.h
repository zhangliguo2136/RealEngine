#pragma once

#include "ParticleSystem.h"

class ParticleScene
{
public:
	ParticleScene();
	~ParticleScene();

	void update(float deltaTime);

private:
	
	ParticleSystem* _particleSystem = nullptr;
};