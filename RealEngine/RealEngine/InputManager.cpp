#include "InputManager.h"
#include <iostream>
#include "Logger.h"

#include "SceneManager.h"

void RealEngine::InputManager::InputKeyDown(int key)
{
	_keys.push_back(key);
}

void RealEngine::InputManager::InputKeyUp(int key)
{
	for (auto iter = _keys.begin(); iter != _keys.end(); iter++)
	{
		if (*iter == key)
		{
			_keys.erase(iter);
			break;
		}
	}
}

void RealEngine::InputManager::InputCursor(double x, double y)
{
	_currCursorX = x;
	_currCursorY = y;
}

void RealEngine::InputManager::InputScroll(double x, double y)
{
	_currScrollX += x;
	_currScrollY += y;
}

void RealEngine::InputManager::InputCursorEnter(bool isEnter)
{
	if (isEnter)
	{
		RealEngine::Log("InputManager:: Input Cursor is enter window\n");
	}
	else
	{
		RealEngine::Log("InputManager:: Input Cursor is left window\n");
	}
}

Vector2d RealEngine::InputManager::getCursorPosition() 
{
	return Vector2d(_currCursorX, _currCursorY);
}

Vector2d RealEngine::InputManager::getScrollPosition() 
{
	return Vector2d(_currScrollX, _currScrollY);
}

bool RealEngine::InputManager::isPressed(int key)
{
	for (auto iter = _keys.begin(); iter != _keys.end(); iter++)
	{
		if (*iter == key)
		{
			return true;
		}
	}

	return false;
}