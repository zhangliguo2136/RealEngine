#include "ThreadPool.h"

RealEngine::ThreadPool::ThreadPool():b_started(false)
{
}

RealEngine::ThreadPool::~ThreadPool() 
{
	if (b_started) 
	{
		stop();
	}
}

void RealEngine::ThreadPool::start()
{
	int coreCount = std::thread::hardware_concurrency();
	_threads.reserve(coreCount);

	for (int i = 0; i < coreCount; i++) 
	{
		_threads.push_back(new std::thread(std::bind(&ThreadPool::onThreadAllocator, this)));
	}

	b_started = true;
}

void RealEngine::ThreadPool::stop()
{
	b_started = false;

	for (std::vector<std::thread*>::iterator iter = _threads.begin(); iter != _threads.end(); iter++)
	{
		(*iter)->join();
		delete *iter;
	}

	_threads.clear();
}

void RealEngine::ThreadPool::addThreadTask(std::function<void()> func) 
{
	_tasks.push(func);
}


std::function<void()> RealEngine::ThreadPool::nextTask()
{
	std::function<void()> _func = nullptr;
	if (!_tasks.empty() && b_started)
	{
		_func = _tasks.front();
		_tasks.pop();
	}

	return _func;
}
void RealEngine::ThreadPool::onThreadAllocator() 
{
	while (b_started) 
	{
		std::function<void()> func = nextTask();

		if (func) 
		{
			func();
		}
	}
}