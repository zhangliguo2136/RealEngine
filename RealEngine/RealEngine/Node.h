#pragma once

#include <vector>

#include "Vector.h"
//#include "GCObjectPool.h"

class Node
{
public:
	Node() {};
	~Node() {};

public:
	void onEnter();
	void onExit();

public:
	virtual void onDraw();

public:
	void addChild(Node* node);
	void removeChild(Node* node);
private:
	std::vector<Node*> _childrens;

public:
	void setPosition(int x, int y);
	Vector2i getPosition() { return _position; };

	void setSize(int x, int y);
	Vector2i getSize() { return _size; }

	void setRotation(int x, int y);
	Vector2i getRotation() { return _rotate; }

	void setScale(float x, float y);
	Vector2f getScale() { return _scale; }

private:
	Vector2i _position = Vector2i(0, 0);
	Vector2i _size = Vector2i(0, 0);
	Vector2i _rotate = Vector2i(0, 0);
	Vector2f _scale = Vector2f(1.0f, 1.0f);
};