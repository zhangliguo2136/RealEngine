#include "InputManager.h"
#include <iostream>
#include "Logger.h"

#include "SceneManager.h"

void RealEngine::InputManager::InputKeyDown(int key)
{
	m_keys.push_back(key);

	SceneManager& pManager = SceneManager::getInstance();
	pManager.processKeyDown(key);
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

	SceneManager& pManager = SceneManager::getInstance();
	pManager.processKeyUp(key);
}

void RealEngine::InputManager::InputCursor(double x, double y)
{
	m_currCursorX = x;
	m_currCursorY = y;


	SceneManager& pManager = SceneManager::getInstance();
	pManager.processCursor(x, y);
}

void RealEngine::InputManager::InputScroll(double x, double y)
{
	SceneManager& pManager = SceneManager::getInstance();
	pManager.processScroll(x, y);
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