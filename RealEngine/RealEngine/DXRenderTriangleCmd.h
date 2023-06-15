#pragma once
#include "RenderCommand.h"

class DXRenderTriangleCmd :public RenderCommand
{
public:
	virtual void execute() override;

public:
	DXRenderTriangleCmd();
	~DXRenderTriangleCmd();
};