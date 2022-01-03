#include "SceneManager.h"
#include "Image.h"
#include "Model.h"
#include "Matrix.h"
#include <math.h>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "Logger.h"

RealEngine::SceneManager::SceneManager() 
{
	_camera = new Camera();
}
RealEngine::SceneManager::~SceneManager() 
{
	delete _camera;
	_camera = nullptr;
}

void RealEngine::SceneManager::addSceneObject(IBaseObject* object)
{
	_objects.push_back(object);
}

void RealEngine::SceneManager::Tick() 
{
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	float deltaTime = ms.count() - _lastTime;
	_lastTime = ms.count();

	// view projection 处理

	Matrix4 view = _camera->getViewMatrix();
	Matrix4 projection = _camera->getProjectionMatrix();

	// 更新
	_bUpdatingObjects = true;
	for (auto iter = _objects.begin(); iter != _objects.end(); ++iter)
	{
		(*iter)->updateTransform(view, projection);

		(*iter)->update(deltaTime);
	}
	_bUpdatingObjects = false;


	_bObjectsRendering = true;
	for (auto iter = _objects.begin(); iter != _objects.end(); ++iter)
	{
		(*iter)->draw();
	}
	_bObjectsRendering = false;
}