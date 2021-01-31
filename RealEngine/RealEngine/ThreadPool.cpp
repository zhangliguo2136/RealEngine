#include "ThreadPool.h"

RealEngine::ThreadPool::ThreadPool() 
{
	int coreCount = std::thread::hardware_concurrency();
	threads.reserve(coreCount);
}

RealEngine::ThreadPool::~ThreadPool() 
{

}

void RealEngine::ThreadPool::addThreadTask(std::function<void()> func) 
{
	tasks.push_back(func);
}


void RealEngine::ThreadPool::nextTask()
{

}
void RealEngine::ThreadPool::threadAllocator() 
{

}