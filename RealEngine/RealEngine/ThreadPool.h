#pragma once
#include <functional>
#include <Thread>
#include <vector>
#include <queue>

namespace RealEngine
{
	class ThreadPool 
	{
	public:
		ThreadPool();
		~ThreadPool();

		void addThreadTask(std::function<void()> func);
		void start();
		void stop();
	private:
		// 任务分配函数
		void onThreadAllocator();
		std::function<void()> nextTask();

		// 线程
		std::vector<std::thread*> _threads;
		// 线程任务
		std::queue<std::function<void()>> _tasks;

		bool b_started;
	};
}