#pragma once
#include "GCObject.h"

class GCObjectPool
{
public:
	template<class T>
	static T* NewObject(GCObject* obj = nullptr);
};

template<class T>
T* GCObjectPool::NewObject(GCObject* superObj /*=nullptr*/) 
{
	//T* obj = new T();

	void* p = malloc(sizeof(T));
	//void* p = RealEngine::MemoryManager::Allocate(sizeof(T));

	T* obj = new(p) T;

	return obj;
}