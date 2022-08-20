#include "Node.h"
#include <memory>

void Node::onDraw()
{
	for (auto child : _childrens)
	{
		child->onDraw();
	}
}

void Node::onEnter() 
{
	for (auto child : _childrens)
	{
		child->onEnter();
	}
}
void Node::onExit()
{
	for (auto child : _childrens)
	{
		child->onExit();
	}
}

void Node::setPosition(int px, int py)
{
	_position.x = px;
	_position.y = py;
}

void Node::setSize(int sx, int sy)
{
	_size.x = sx;
	_size.y = sy;
}

void Node::setRotation(int rx, int ry)
{
	_rotate.x = rx;
	_rotate.y = ry;
}

void Node::setScale(float sx, float sy)
{
	_scale.x = sx;
	_scale.y = sy;
}

void Node::addChild(Node* node)
{
	if (node)
	{
		_childrens.push_back(node);
		node->onEnter();
	}
}

void Node::removeChild(Node* node)
{
	if (node)
	{
		for (auto iter = _childrens.begin(); iter != _childrens.end(); iter++)
		{
			if (*iter == node)
			{
				node->onExit();
				_childrens.erase(iter);
				break;
			}
		}
	}
}