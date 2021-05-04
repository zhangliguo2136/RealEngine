#include "SceneManager.h"

#include "Image.h"

RealEngine::SceneManager::SceneManager()
{
}

RealEngine::SceneManager::~SceneManager()
{
}

void RealEngine::SceneManager::render()
{
	for (auto iter = _objects.begin(); iter != _objects.end(); ++iter)
	{
		(*iter)->draw();
	}
}

void RealEngine::SceneManager::addSceneObject(ISceneObject* object)
{
	_objects.push_back(object);
}

void RealEngine::SceneManager::Tick() 
{
	Image image;
	image.loadFromFile("../Resource/image/test1.png");
}