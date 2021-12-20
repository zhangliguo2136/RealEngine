#include "SceneManager.h"
#include "Image.h"
#include "Model.h"

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
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	float deltaTime = ms.count() - _lastTime;
	_lastTime = ms.count();

	_bUpdatingObjects = true;
	for (auto iter = _objects.begin(); iter != _objects.end(); ++iter)
	{
		(*iter)->update(deltaTime);
	}
	_bUpdatingObjects = false;


	//Image* image = new Image("../Resource/image/test1.jpg");
	//image->draw();
	//delete image;

	Model* model = new Model("../Resource/model/diablo3_pose.obj");
	model->draw();
	delete model;
}