#pragma once

#include <iostream>
#include "RenderGLComputeParticleCmd.h"

class GLComputeParticle
{
public:
	GLComputeParticle();
	GLComputeParticle(int count);
	~GLComputeParticle();

public:
	void update(float deltaTime);

private:
	int pCount = 0;

	std::shared_ptr<RenderGLComputeParticleCmd> glComputeParticleCmd;
};