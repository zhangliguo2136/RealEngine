#pragma once
#include <list>
namespace RealEngine 
{
	template<class Object>
	class ObjectPool
	{
	public:
		ObjectPool(size_t size);
		virtual ~ObjectPool();

		Object* getObject();
		void returnObject(Object* pObj);

	private:
		size_t _nSize;
		std::list<Object*> _mPool;
	};
}