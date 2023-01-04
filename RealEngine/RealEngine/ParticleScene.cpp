#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
	_particle = new Particle();
}

ParticleScene::~ParticleScene()
{
	delete _particle;
}

void ParticleScene::update(float deltaTime)
{
	_particle->update(deltaTime);
}