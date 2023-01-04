#pragma once

#include "RenderCommand.h"
#include <vector>

class RenderParticleCmd :public RenderCommand
{
public:
	virtual void execute() override;

public:
	RenderParticleCmd();
	~RenderParticleCmd();

public:
	int ParticleCount = 0;

	unsigned ParticleTextureID = -1;

	std::vector<Vector3f> Velocitys;
	std::vector<Vector3f> Positions;
	std::vector<Vector4f> Colors;
	std::vector<float> Lifes;

private:
	unsigned int _vao = -1;
	unsigned int _positionBuffer = -1;
};
