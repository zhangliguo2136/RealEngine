#pragma once

#include "Text.h"
#include "Canvas.h"

class UISystem
{
public:
	UISystem();
	~UISystem();

	static UISystem& getInstance()
	{
		static UISystem instance;
		return instance;
	}

	UISystem(const UISystem&) = delete;
	UISystem& operator = (const UISystem&) = delete;

public:
	void Tick();
private:
	// ��¼ʱ��������룩
	long long _lastTime = 0;
private:
	Text* _frameText = nullptr;

	Canvas* _scene = nullptr;
};