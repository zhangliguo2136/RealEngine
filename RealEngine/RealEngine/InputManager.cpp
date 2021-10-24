#include "InputManager.h"
#include <iostream>
#include "Logger.h"

void RealEngine::InputManager::InputKeyDown(int key)
{
	m_keys.push_back(key);
}

void RealEngine::InputManager::InputKeyUp(int key)
{
	for (auto iter = m_keys.begin(); iter != m_keys.end(); iter++)
	{
		if (*iter == key)
		{
			m_keys.erase(iter);
			break;
		}
	}
}

void RealEngine::InputManager::InputCursor(double x, double y)
{
	m_currCursorX = x;
	m_currCursorY = y;
}

void RealEngine::InputManager::InputScroll(double x, double y)
{

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
