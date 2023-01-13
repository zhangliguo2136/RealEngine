#include "RayTraceScene.h"
#include "RenderSystem.h"

RayTraceScene::RayTraceScene()
{
	pathTracingCmd = std::make_shared<RenderPathTracingCmd>();
}

RayTraceScene::~RayTraceScene()
{
	pathTracingCmd = nullptr;
}

void RayTraceScene::update(float deltaTime)
{
	auto& renderSys = RenderSystem::getInstance();
	renderSys.AddCommand(pathTracingCmd);
}