#pragma once
#include <list>
namespace RealEngine 
{
	template<class Object>
	class ObjectPool
	{
	public:
		ObjectPool(size_t size, std::string className);
		virtual ~ObjectPool();

		Object* getObject();
		void returnObject(Object* pObj);

		std::string getClassName()
		{
			return _sClassName;
		}
	private:
		std::string _sClassName;
	private:
		size_t _nSize;
		std::list<Object*> _mPool;
	};
}