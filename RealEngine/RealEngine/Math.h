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


namespace Math
{
	float radians(float angle);
}

