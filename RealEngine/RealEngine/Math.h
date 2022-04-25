#pragma once
class Size
{
public:
	Size() {};
	~Size() {};
public:
	Size(float inWidth, float inHeight) 
	{
		width = inWidth;
		height = inHeight;
	}
public:
	float width, height;
};

class Vector3f;
namespace Math
{
	float radians(float angle);

	float random_float();

	Vector3f random_vector(float minmag = 0.0f, float maxmag = 1.0f);
}

