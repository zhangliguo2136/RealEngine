#pragma once

#include "RenderCommand.h"
#include <vector>

class RenderGLComputeParticleCmd :public RenderCommand
{
public:
	virtual void execute() override;

public:
	RenderGLComputeParticleCmd();
	~RenderGLComputeParticleCmd();

public:
	void update(float deltaTime);

public:
	int ParticleCount = 0;
};
