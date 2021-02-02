#pragma once
#include <functional>
#include <Thread>
#include <vector>
#include <queue>

// 线程锁
#include <mutex>
#include <condition_variable>
#include <utility>

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

		// 互斥锁
		std::mutex m_mtx;
		// 条件变量
		std::condition_variable m_cv;
	};
}