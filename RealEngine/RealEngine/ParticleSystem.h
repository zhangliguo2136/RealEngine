#pragma once

#include "Vector.h"

class Particle
{
	Vector3f Position;	// 位置
	Vector3f Velocity;	// 速度
	Vector4f Color;		// 颜色

	float Life;			// 生命时常
};	

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
};