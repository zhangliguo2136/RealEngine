#include "ModelScene.h"
#include "GLShaderCache.h"

RealEngine::ModelScene::ModelScene()
{
	_camera = new Camera();

	_assimpModel = new AssimpModel("../Resource/models/nanosuit/nanosuit.obj");
}

RealEngine::ModelScene::~ModelScene()
{

}

void RealEngine::ModelScene::update(float deltaTime)
{
	_camera->update(deltaTime);
	glEnable(GL_DEPTH_TEST);

	// »æÖÆ½×¶Î
	auto shader = GLShaderCache::getInstance().findOrCreate("Model");
	shader->UseProgram();

	auto view = _camera->getViewMatrix();
	auto projection = _camera->getProjectionMatrix();

	shader->setUniformMatrix4fv("projection", projection.data());
	shader->setUniformMatrix4fv("view", view.data());

	_assimpModel->draw(*shader);
}