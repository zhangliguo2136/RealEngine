#include "RenderQueue.h"

RenderQueue::RenderQueue()
{

}

RenderQueue::~RenderQueue()
{

}

void RenderQueue::Push(RenderCommand cmd) 
{
	_commands.push(cmd);
}
RenderCommand RenderQueue::Front() 
{
	return _commands.front();
}