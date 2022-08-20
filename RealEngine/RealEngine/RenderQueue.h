#pragma once
#include <queue>
#include <memory>

#include "RenderCommand.h"

class RenderCommand;

class RenderQueue
{
public:
	RenderQueue();
	~RenderQueue();

	void Push(std::shared_ptr<RenderCommand> cmd);
	std::shared_ptr<RenderCommand> Front();

	bool isEmpty();
private:
	std::queue<std::shared_ptr<RenderCommand> > _commands;
};