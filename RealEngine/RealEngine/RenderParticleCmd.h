#pragma once

#include "RenderCommand.h"

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

private:
	unsigned int _vao = -1;
	unsigned int _positionBuffer = -1;
};
