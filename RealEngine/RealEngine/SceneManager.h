#pragma once

#include <vector>
#include <chrono>
#include <iostream>
#include "Math.h"
#include "Scene.h"

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

		Size getWinSize()
		{
			return Size(1920, 1080);
		};

	private:
		Scene* _scene = nullptr;

		float _lastTime = 0.0f;
	};
}