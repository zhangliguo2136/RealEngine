#include "ParticleSystem.h"

#include <string>

#include "Math.h"
#include "TextureGLCache.h"
#include "RenderSystem.h"

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

	auto buffer = TextureGLCache::getInstance().findOrCreate("../Resource/images/particle.png");

	_renderCmd = std::make_shared<RenderParticleCmd>();
	_renderCmd->ParticleCount = _particleCount;
	_renderCmd->ParticleTextureID = buffer->getTextureID();
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


	RenderSystem::getInstance().AddCommand(_renderCmd);
}