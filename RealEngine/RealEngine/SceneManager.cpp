#include "SceneManager.h"

#include "Logger.h"
#include "Matrix.h"
#include "TimeUtils.h"

RealEngine::SceneManager::SceneManager() 
{
	_lastTime = getMillSecondTime();
	_scene = new ParticleScene();
}
RealEngine::SceneManager::~SceneManager() 
{
	delete _scene;
	_scene = nullptr;
}


void RealEngine::SceneManager::Tick() 
{
	auto currTime = getMillSecondTime();
	float deltaTime = (float)(currTime - _lastTime)/1000.f;
	_lastTime = currTime;

	// ¸üĞÂ³¡¾°
	//_scene->update(deltaTime);
}