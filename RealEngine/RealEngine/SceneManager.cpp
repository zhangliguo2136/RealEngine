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
	_viewProj = new Matrix4();
	_viewProj->Identity();

	_uWorldTransform = new Matrix4();
	_uWorldTransform->Identity();
}

RealEngine::SceneManager::~SceneManager()
{

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

	_bUpdatingObjects = true;
	for (auto iter = _objects.begin(); iter != _objects.end(); ++iter)
	{
		(*iter)->updateTransform(_viewProj, _uWorldTransform);

		(*iter)->update(deltaTime);
	}
	_bUpdatingObjects = false;


	_bObjectsRendering = true;
	for (auto iter = _objects.begin(); iter != _objects.end(); ++iter)
	{
		(*iter)->draw();
	}
	_bObjectsRendering = false;

	//Image* image = new Image("../Resource/image/test1.jpg");
	//image->draw();
	//delete image;
}


void RealEngine::SceneManager::processKeyDown(int key)
{
	if (key == REKey::REKEY_MOUSE_LEFT)
	{
		_isMoving = true;
	}
}

void RealEngine::SceneManager::processKeyUp(int key) 
{
	if (key == REKey::REKEY_MOUSE_LEFT)
	{
		_isMoving = false;

		_cursorX = 0;
		_cursorY = 0;
	}
}

void RealEngine::SceneManager::processCursor(double x, double y) 
{
	if (_isMoving)
	{

		if (_cursorX > 0 && _cursorY > 0)
		{
			double movementX = x - _cursorX;
			double movementY = y - _cursorY;

			Size winSize = this->getWinSize();

			double angleX = (movementX * 360) / winSize.width;
			double angleY = (movementY * 360) / winSize.height;


			Matrix4 rotationX;
			rotationX.Identity();
			float* xData = rotationX.GetMatrixData();
			xData[5] = cos(angleX);
			xData[6] = -sin(angleX);
			xData[9] = sin(angleX);
			xData[10] = cos(angleX);


			Matrix4 rotationY;
			rotationY.Identity();
			float* yData = rotationY.GetMatrixData();
			yData[1] = cos(angleY);
			yData[3] = sin(angleY);
			yData[8] = -sin(angleY);
			yData[10] = cos(angleY);


			//Matrix4 rotationZ;
			//rotationZ.Identity();
			//float* zData = rotationY.GetMatrixData();
			//zData[0] = cos(angleZ);
			//zData[1] = -sin(angleZ);
			//zData[4] = sin(angleZ);
			//zData[5] = cos(angleZ);

			Matrix4 rotation = (*_uWorldTransform) * rotationX * rotationY;

			printf("processCursor movement(%f, %f) angle (%f, %f)\n", movementX, movementY, angleX, angleY);

			_uWorldTransform->copyForm(rotation);
		}
		else
		{
			_cursorX = x;
			_cursorY = y;
		}
	}
}

void RealEngine::SceneManager::processScroll(double x, double y) 
{

	// TODO Ä£ÐÍËõ·Å
	//_scale = _scale + y / 100.0f;
	//_scale = _scale < 0.0f ? 0.0f : _scale;

	//Matrix4 scaleMat = Matrix4::CreateScaleMatrix(Vector3f(_scale - 1.f, _scale - 1.f, _scale - 1.f));

	//Matrix4 scale = (*_uWorldTransform) * scaleMat;

	//printf("processScroll scroll(%f, %f, %f)\n", x, y, _scale);

	//_uWorldTransform->copyForm(scale);
}