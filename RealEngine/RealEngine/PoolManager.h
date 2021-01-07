#pragma once
#include <iostream>
#include <map>

#include "ObjectPool.h"

namespace RealEngine 
{
	template<class Object>
	class PoolManager 
	{
	public:
		~PoolManager() 
		{
			printf("PoolManager: detructor called...");
		}

		static PoolManager& getInstance() 
		{
			static PoolManager s_pInstance;
			return s_pInstance;
		}

		PoolManager(const PoolManager&) = delete;
		PoolManager& operator=(const PoolManager&) = delete;
	private:
		PoolManager() 
		{
			printf("PoolManager: constructor called...");
		}

	public:
		Object* getObject(std::string className);
		void returnObject(Object* pObj);
	private:
		std::map<std::string, RealEngine::ObjectPool<Object>> _mPools;
	};
}