#pragma once

#include "Camera.h"
#include "AssimpModel.h"
#include "glmCamera.h"

namespace RealEngine
{
	class ModelScene
	{
	public:
		ModelScene();
		~ModelScene();

		void update(float deltaTime);

	private:
		Camera* _camera = nullptr;
		glmCamera* _glmCamera = nullptr;
		AssimpModel* _assimpModel = nullptr;
	};
}