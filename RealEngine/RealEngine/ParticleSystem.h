#pragma once

#include "Vector.h"

class Particle
{
	Vector3f Position;	// λ��
	Vector3f Velocity;	// �ٶ�
	Vector4f Color;		// ��ɫ

	float Life;			// ����ʱ��
};	

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
};