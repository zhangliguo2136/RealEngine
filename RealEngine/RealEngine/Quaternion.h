#pragma once
class Vector3f;
/*
	ËÄÔªÊý
*/
class Quaternion 
{
public:
	float x, y, z, w;

	explicit Quaternion(float inX, float inY, float inZ, float inW);
	explicit Quaternion(Vector3f& axis, float angle);
};