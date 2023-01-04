#include "Particle.h"

#include <string>

#include "Math.h"
#include "TextureGLCache.h"
#include "RenderSystem.h"

Particle::Particle() : Particle(50000)
{

}

Particle::Particle(int count): pCount(count)
{
	for (auto i = 0; i < pCount; ++i)
	{
		Positions.push_back(Math::random_vector());
		Velocitys.push_back(Math::random_vector());
		Colors.push_back(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		Lifes.push_back(Math::random_float());
	}

	auto buffer = TextureGLCache::getInstance().findOrCreate("../Resource/images/particle.png");

	_renderCmd = std::make_shared<RenderParticleCmd>();
	_renderCmd->ParticleCount = pCount;
	_renderCmd->ParticleTextureID = buffer->getTextureID();
}

Particle::~Particle()
{
	_renderCmd = nullptr;
}

void Particle::update(float deltaTime)
{
	std::vector<Vector3f> Positions;
	std::vector<Vector3f> Velocitys;
	std::vector<Vector4f> Colors;
	std::vector<float> Lifes;

	for (auto i = 0; i < pCount; ++i)
	{
		auto& Life = this->Lifes[i];
		auto& Position = this->Positions[i];
		auto& Color = this->Colors[i];
		auto& Velocity = this->Velocitys[i];

		Life -= deltaTime;

		if (Life > 0.0f)
		{
			Position = Position - Velocity * deltaTime;
			Color.w = Color.w - deltaTime * 0.25;
		}
		else
		{
			Life = Math::random_float();
			Color.w = 1.0f;
			Position = Math::random_vector();
		}
	}

	_renderCmd->Positions = Positions;
	_renderCmd->Velocitys = Velocitys;
	_renderCmd->Colors = Colors;
	_renderCmd->Lifes = Lifes;

	RenderSystem::getInstance().AddCommand(_renderCmd);
}