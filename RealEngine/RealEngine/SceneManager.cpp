#include "SceneManager.h"

#include <math.h>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "Logger.h"
#include "Matrix.h"

RealEngine::SceneManager::SceneManager() 
{
	_frameText = new Text();

	_scene = new ParticleScene();
}
RealEngine::SceneManager::~SceneManager() 
{
	delete _scene;
	_scene = nullptr;
}


void RealEngine::SceneManager::Tick() 
{
	float deltaTime = glfwGetTime() - _lastTime;
	_lastTime = glfwGetTime();

	// ���³���
	_scene->update(deltaTime);

	//��ʾ֡��
	_frameText->setText(1.0f / deltaTime);
	_frameText->draw();
}