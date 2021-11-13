#include "Bezier.h"

void Bezier2D::addController(Vector2f point)
{
	m_controller.push_back(point);
}

void Bezier2D::draw()
{
	for (int i = 0; i < 100; ++i)
	{
		this->recursion(m_controller, i);
	}
}

void Bezier2D::recursion(std::vector<Vector2f> points, int dt)
{
	std::vector<Vector2f> newPoints;

	Vector2f* last = nullptr;
	for (auto point : points)
	{
		Vector2f dtpoint = this->getVector2f(*last, point, dt);
		newPoints.push_back(dtpoint);

		last = &point;
	}

	if (newPoints.size() < 2)
	{
		printf("Bezer2D:: the line point is {%d, %d}", newPoints[0].x, newPoints[0].y);
		return;
	}
}

Vector2f Bezier2D::getVector2f(Vector2f begin, Vector2f end, int dt)
{
	Vector2f ret;
	ret.x = begin.x + (end.x - begin.x) * dt / 100;
	ret.y = begin.y + (end.y - begin.y) * dt / 100;
	return ret;
}