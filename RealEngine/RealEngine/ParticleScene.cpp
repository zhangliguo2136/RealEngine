#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
	_particleSystem = new ParticleSystem();
}

ParticleScene::~ParticleScene()
{
	delete _particleSystem;
}

void ParticleScene::update(float deltaTime)
{
	_particleSystem->update(deltaTime);
}