#pragma once

#include <vector>
#include <memory>

#include "Vector.h"
#include "RenderParticleCmd.h"

class Particle
{
public:
	Particle();
	Particle(int count);
	~Particle();

	void update(float deltaTime);

private:
	int pCount = 0;

	std::vector<Vector3f> Positions;
	std::vector<Vector3f> Velocitys;
	std::vector<Vector4f> Colors;
	std::vector<float> Lifes;

	std::shared_ptr<RenderParticleCmd> _renderCmd = nullptr;
};