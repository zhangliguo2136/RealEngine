#pragma once
#include <iostream>
#include "IApplication.h"

struct EConfig
{
	int Width = 1920;
	int Height = 1080;
	std::string Name = "RealEngine";
};

///*
//ThreadPool ²âÊÔ
//*/
//#include "ThreadPool.h"
//using namespace RealEngine;
//void threadPoolTest1() { printf("threadPoolTest: out num is %d\n", 1); }
//void threadPoolTest2() { printf("threadPoolTest: out num is %d\n", 2); }
//void threadPoolTest3() { printf("threadPoolTest: out num is %d\n", 3); }
//void threadPoolTest4() { printf("threadPoolTest: out num is %d\n", 4); }
//void threadPoolTest5() { printf("threadPoolTest: out num is %d\n", 5); }
//void threadPoolTest6() { printf("threadPoolTest: out num is %d\n", 6); }
//void threadPoolTest7() { printf("threadPoolTest: out num is %d\n", 7); }
//void threadPoolTest8() { printf("threadPoolTest: out num is %d\n", 8); }
//void threadPoolTest9() { printf("threadPoolTest: out num is %d\n", 9); }
//void threadPoolTest10() { printf("threadPoolTest: out num is %d\n", 10); }
//void threadPoolTest()
//{
//	RealEngine::ThreadPool* pool = new RealEngine::ThreadPool();
//	pool->addThreadTask(threadPoolTest1);
//	pool->addThreadTask(threadPoolTest2);
//	pool->addThreadTask(threadPoolTest3);
//	pool->addThreadTask(threadPoolTest4);
//	pool->addThreadTask(threadPoolTest5);
//	pool->addThreadTask(threadPoolTest6);
//	pool->addThreadTask(threadPoolTest7);
//	pool->addThreadTask(threadPoolTest8);
//	pool->addThreadTask(threadPoolTest9);
//	pool->addThreadTask(threadPoolTest10);
//
//	pool->start();
//	std::this_thread::sleep_for(std::chrono::seconds(1));
//	pool->stop();
//}
//
//#include "EngineTest.h"

