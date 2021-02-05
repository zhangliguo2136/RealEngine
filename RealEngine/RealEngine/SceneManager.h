#pragma once

#include <vector>
#include "ISceneObject.h"

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
		void render();

		void addSceneObject(ISceneObject* object);

	private:
		std::vector<ISceneObject*> _objects;
	};
}