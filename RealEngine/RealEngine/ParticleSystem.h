#pragma once

#include <vector>

#include "Vector.h"
#include "Shader.h"

class Particle
{
public:
	Vector3f Position;	// λ��
	Vector3f Velocity;	// �ٶ�
	Vector4f Color;		// ��ɫ

	float Life;			// ����ʱ��

	Particle(): 
		Position(0.0f, 0.0f, 0.0f), 
		Velocity(0.0f, 0.0f, 0.0f),
		Color(1.0f, 1.0f, 1.0f, 1.0f),
		Life(1.0f) 
	{ }
};	

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void update(float deltaTime);

private:
	std::vector<Particle> _particles;

	long long _particleCount = 100000;

	unsigned int _vao;
	unsigned int _positionBuffer;
	unsigned int _textureID;

	Shader* _shader = nullptr;
};