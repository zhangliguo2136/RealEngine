#pragma once
#include <queue>

#include "RenderCommand.h"

class RenderCommand;

class RenderQueue
{
public:
	RenderQueue();
	~RenderQueue();

	void Push(RenderCommand cmd);
	RenderCommand Front();

private:
	std::queue<RenderCommand> _commands;
};