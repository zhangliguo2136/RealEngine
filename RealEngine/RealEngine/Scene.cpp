#include "Scene.h"

RealEngine::Scene::Scene()
{
	_camera = new Camera();

	_model = new Model("../Resource/models/nanosuit/nanosuit.obj");
	_modelShader = new Shader("../Resource/shaders/Model.vs", "../Resource/shaders/Model.fs");
}

RealEngine::Scene::~Scene()
{

}

void RealEngine::Scene::update(float deltaTime)
{
	_camera->update(deltaTime);
	glEnable(GL_DEPTH_TEST);

	// »æÖÆ½×¶Î
	_modelShader->useProgram();

	auto view = _camera->getViewMatrix();
	auto projection = _camera->getProjectionMatrix();

	_modelShader->setMatrixUniform("projection", projection.data());
	_modelShader->setMatrixUniform("view", view.data());

	_model->draw(*_modelShader);
}