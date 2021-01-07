#include "ObjectPool.h"

template<class Object>
RealEngine::ObjectPool<Object>::ObjectPool(size_t size)
{
	_nSize = size;

	for (size_t n = 0; n < _nSize; n++)
	{
		_mPool.push_back(new Object());
	}
}

template<class Object>
RealEngine::ObjectPool<Object>::~ObjectPool()
{
	auto *iter = _mPool.begin();
	while (iter != _mPool.end())
	{
		delete *iter;
		++iter;
	}
	_nSize = 0;
}

template<class Object>
Object* RealEngine::ObjectPool<Object>::getObject()
{
	Object* pObj = nullptr;
	if (_nSize == 0) 
	{
		pObj = new Object();
	}
	else
	{
		pObj = _mPool.front();
		_mPool.pop_front();
		--_nSize;
	}

	return pObj;
}

template<class Object>
void RealEngine::ObjectPool<Object>::returnObject(Object* pObj)
{
	_mPool.push_back(pObj);
	++_nSize;
}