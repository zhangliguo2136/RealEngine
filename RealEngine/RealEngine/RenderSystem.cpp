#include "RenderSystem.h"
#include "RenderCommand.h"

#include <memory>

RenderSystem::RenderSystem()
{
	_renderQueue = new RenderQueue();
}

RenderSystem::~RenderSystem()
{
	if (_renderQueue)
	{
		delete _renderQueue;
		_renderQueue = nullptr;
	}
}

void RenderSystem::Tick()
{
	while (!_renderQueue->isEmpty())
	{
		auto command = _renderQueue->Front();
		command->execute();
	};
}

void RenderSystem::AddCommand(std::shared_ptr<RenderCommand> cmd)
{
	_renderQueue->Push(cmd);
}