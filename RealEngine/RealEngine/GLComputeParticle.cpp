#include "GLComputeParticle.h"

GLComputeParticle::GLComputeParticle() :GLComputeParticle(50000)
{

}

GLComputeParticle::GLComputeParticle(int count) : pCount(count)
{
	glComputeParticleCmd = std::make_shared<RenderGLComputeParticleCmd>();
	glComputeParticleCmd->ParticleCount = pCount;
}

GLComputeParticle::~GLComputeParticle()
{

}

void GLComputeParticle::update(float deltaTime)
{
	glComputeParticleCmd->update(deltaTime);
	glComputeParticleCmd->execute();
}