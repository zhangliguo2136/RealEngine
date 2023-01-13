#pragma once
#include <memory>

#include "RenderPathTracingCmd.h"

class RayTraceScene
{
public:
	RayTraceScene();
	~RayTraceScene();

	void update(float deltaTime);

private:
	std::shared_ptr<RenderPathTracingCmd> pathTracingCmd;
};