#include "SceneManager.h"

#include <math.h>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "Logger.h"
#include "Matrix.h"

RealEngine::SceneManager::SceneManager() 
{
	_scene = new Scene();
}
RealEngine::SceneManager::~SceneManager() 
{
	delete _scene;
	_scene = nullptr;
}


void RealEngine::SceneManager::Tick() 
{
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	float deltaTime = ms.count() - _lastTime;
	_lastTime = ms.count();

	// ¸üÐÂ³¡¾°
	_scene->update(deltaTime);
}