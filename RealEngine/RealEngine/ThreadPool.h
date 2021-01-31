#pragma once
#include <functional>
#include <Thread>
#include <vector>

namespace RealEngine
{
	class ThreadPool 
	{
	public:
		ThreadPool();
		~ThreadPool();

		void addThreadTask(std::function<void()> func);

	private:
		// 任务分配函数
		void threadAllocator();
		void nextTask();

		// 线程
		std::vector<std::thread> threads;
		// 线程任务
		std::vector<std::function<void()>> tasks;
	};
}