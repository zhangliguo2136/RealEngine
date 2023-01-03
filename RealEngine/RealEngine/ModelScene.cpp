#include "ModelScene.h"

RealEngine::ModelScene::ModelScene()
{
	_camera = new Camera();

	_assimpModel = new AssimpModel("../Resource/models/nanosuit/nanosuit.obj");
	_modelShader = new Shader("../Resource/shaders/Model.vs", "../Resource/shaders/Model.fs");
}

RealEngine::ModelScene::~ModelScene()
{

}

void RealEngine::ModelScene::update(float deltaTime)
{
	_camera->update(deltaTime);
	glEnable(GL_DEPTH_TEST);

	// »æÖÆ½×¶Î
	_modelShader->useProgram();

	auto view = _camera->getViewMatrix();
	auto projection = _camera->getProjectionMatrix();

	_modelShader->setUniformMatrix4fv("projection", projection.data());
	_modelShader->setUniformMatrix4fv("view", view.data());

	_assimpModel->draw(*_modelShader);
}