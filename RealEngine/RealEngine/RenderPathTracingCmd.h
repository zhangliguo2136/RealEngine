#pragma once

#pragma once
#include "RenderCommand.h"

class RenderPathTracingCmd :public RenderCommand
{
public:
	virtual void execute() override;

public:
	RenderPathTracingCmd();
	~RenderPathTracingCmd();

private:
	unsigned int _vao, _vbo, _ebo;
};