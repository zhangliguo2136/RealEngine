#pragma once
#include "Vector.h"

struct TRotator
{
	float Roll;
	float Pitch;
	float Yaw;

	TRotator() :Roll(0.f), Pitch(0.f), Yaw(0.f) {}

	TRotator(float InRoll, float InPitch, float InYaw)
		:Roll(InRoll), Pitch(InPitch), Yaw(InYaw) {}

	static const TRotator Zero;
};

class TTransform
{
public:
	TTransform()
	{
		Location = TVector3f::Zero;
		Rotation = TRotator::Zero;
		Scale = TVector3f::One;
	}

public:
	TVector3f Location;
	TRotator Rotation;
	TVector3f Scale;
};
