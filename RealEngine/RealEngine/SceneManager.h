#pragma once

#include <vector>
#include <chrono>
#include <iostream>
#include "IBaseObject.h"
#include "Math.h"
#include "REKey.h"
#include "Camera.h"
#include "Model.h"

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
			return Size(1920, 1080);
		};

	public:
		Camera* _camera = nullptr;
		Model* _model = nullptr;

	private:
		std::vector<IBaseObject*> _objects;

		float _lastTime = 0.0f;

		// 是否正在执行更新
		bool _bUpdatingObjects = false;

		// 是否正在执行渲染
		bool _bObjectsRendering = false;

	};
}