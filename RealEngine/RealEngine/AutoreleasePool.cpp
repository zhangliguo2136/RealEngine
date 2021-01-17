#include "AutoreleasePool.h"

AutoreleasePool::AutoreleasePool()
	:_name("")
{
	_managedObjectArray.reserve(150);
}

AutoreleasePool::AutoreleasePool(const std::string& name)
	:_name(name)
{
	_managedObjectArray.reserve(150);
}

AutoreleasePool::~AutoreleasePool()
{
	clear();

	PoolManager& s_sInstance = PoolManager::getInstance();
	s_sInstance.pop();
}

void AutoreleasePool::addObject(Ref* object)
{
	_managedObjectArray.push_back(object);
}

void AutoreleasePool::clear()
{
	std::vector<Ref*> releasings;
	releasings.swap(_managedObjectArray);
	for (const auto& obj : releasings)
	{
		obj->release();
	}
}

/*
-------------------------------------------------
PoolManager
-------------------------------------------------
*/

PoolManager::PoolManager()
{
	_releasePoolStack.reserve(10);
}

PoolManager::~PoolManager()
{
	while (!_releasePoolStack.empty()) 
	{
		AutoreleasePool* pool = _releasePoolStack.back();

		delete pool;
	}
}

AutoreleasePool* PoolManager::getCurrentPool() const 
{
	return _releasePoolStack.back();
}

void PoolManager::push(AutoreleasePool *pool)
{
	_releasePoolStack.push_back(pool);
}

void PoolManager::pop()
{
	_releasePoolStack.pop_back();
}


