#include "RenderQueue.h"

RenderQueue::RenderQueue()
{

}

RenderQueue::~RenderQueue()
{
	printf("RenderQueue::remain commands size is %d\n", _commands.size());

	while (!_commands.empty())
	{
		_commands.front();
	}

	printf("RenderQueue::clear command queue is finish\n");
}

void RenderQueue::Push(std::shared_ptr<RenderCommand> cmd)
{
	_commands.push(cmd);
}

std::shared_ptr<RenderCommand> RenderQueue::Front()
{
	auto command  = _commands.front();
	_commands.pop();
	return command;
}

bool RenderQueue::isEmpty()
{
	return _commands.empty();
}