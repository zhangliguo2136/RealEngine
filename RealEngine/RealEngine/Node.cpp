#include "Node.h"
#include <memory>

void Node::draw()
{
	for (auto child : _childrens)
	{
		child->draw();
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
	_px = px;
	_py = py;
}

void Node::setSize(int sx, int sy)
{
	_sx = sx;
	_sy = sy;
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