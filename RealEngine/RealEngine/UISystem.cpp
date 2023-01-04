#include "UISystem.h"
#include "TimeUtils.h"

UISystem::UISystem()
{
	_lastTime = getMillSecondTime();
	_frameText = new Text();

	_scene = new Canvas();
}

UISystem::~UISystem()
{
	if (_frameText)
	{
		delete _frameText;
		_frameText = nullptr;
	}

	if (_scene)
	{
		delete _scene;
		_scene = nullptr;
	}
}

void UISystem::Tick()
{
	auto currTime = getMillSecondTime();
	float deltaTime = (float)(currTime - _lastTime) / 1000.f;
	_lastTime = currTime;

	_scene->onDraw();

	//ÏÔÊ¾Ö¡Êý
	_frameText->setText(1.0f / deltaTime);
	_frameText->onDraw();
}