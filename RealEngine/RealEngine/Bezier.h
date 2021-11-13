#pragma once
#include "Math.h"
#include <vector>

class Bezier2D
{
public:
	Bezier2D() {};
	~Bezier2D() {};

	void addController(Vector2f point);

	void draw();

private:
	void recursion(std::vector<Vector2f> point, int dt);
	Vector2f getVector2f(Vector2f begin, Vector2f end, int dt);

private:
	std::vector<Vector2f> m_controller;
};