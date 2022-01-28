#pragma once

#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "ComputeShader.h"

#include "glmCamera.h"

namespace RealEngine
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void update(float deltaTime);

	private:
		Camera* _camera = nullptr;
		glmCamera* _glmCamera = nullptr;
		Model* _model = nullptr;
		Shader* _modelShader = nullptr;
	};
}