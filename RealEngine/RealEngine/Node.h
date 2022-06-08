#pragma once

#include <vector>

class Node
{
private:
	Node() {};
	~Node() {};

	void draw();

	void onEnter();
	void onExit();

public:
	void setPosition(int x, int y);
	void setSize(int x, int y);

public:
	void addChild(Node* node);

	void removeChild(Node* node);
private:
	std::vector<Node*> _childrens;

private:
	int _px, _py;
	int _sx, _sy;
};