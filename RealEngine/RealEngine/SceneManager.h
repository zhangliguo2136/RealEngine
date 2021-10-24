#pragma once

#include <vector>
#include <chrono>
#include <iostream>
#include "ISceneObject.h"
#include "Math.h"

namespace RealEngine 
{
	class SceneManager 
	{
	public:
		SceneManager() {};
		~SceneManager() {};

		static SceneManager& getInstance()
		{
			static SceneManager instance;
			return instance;
		}

		SceneManager(const SceneManager&) = delete;
		SceneManager& operator = (const SceneManager&) = delete;

	public:
		void Tick();

		void render();
		void addSceneObject(ISceneObject* object);

		Size getWinSize()
		{
			return Size(800.0, 600.0);
		};
	private:
		std::vector<ISceneObject*> _objects;

		float _lastTime = 0.0f;

		// 是否正在执行更新
		bool _bUpdatingObjects = false;
	};
}