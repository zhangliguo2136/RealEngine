#pragma once

#include <vector>
#include <chrono>
#include <iostream>
#include "IBaseObject.h"
#include "Math.h"
#include "REKey.h"

namespace RealEngine 
{
	class SceneManager 
	{
	public:
		SceneManager();
		~SceneManager();

		static SceneManager& getInstance()
		{
			static SceneManager instance;
			return instance;
		}

		SceneManager(const SceneManager&) = delete;
		SceneManager& operator = (const SceneManager&) = delete;

	public:
		void Tick();

		void addSceneObject(IBaseObject* object);

		Size getWinSize()
		{
			return Size(800.0, 600.0);
		};

		Matrix4* _viewProj;
		Matrix4* _uWorldTransform;
	private:
		std::vector<IBaseObject*> _objects;

		float _lastTime = 0.0f;

		// 是否正在执行更新
		bool _bUpdatingObjects = false;

		// 是否正在执行渲染
		bool _bObjectsRendering = false;


	public:
		void processKeyDown(int key);
		void processKeyUp(int key);
		void processCursor(double, double);
		void processScroll(double, double);

		bool _isMoving = false;
		double _cursorX = 0.0;
		double _cursorY = 0.0;

		float _scale = 1.0f;

	};
}