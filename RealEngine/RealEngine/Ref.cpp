#include "Ref.h"
#include "AutoreleasePool.h"

void Ref::release() 
{
	--_referenceCount;
}

void Ref::retain()
{
	++_referenceCount;
}

unsigned int Ref::getReferenceCount() const
{
	return _referenceCount;
}

Ref* Ref::autorelease() 
{
	PoolManager& s_sInstance = PoolManager::getInstance();
	auto pool = s_sInstance.getCurrentPool();
	pool->addObject(this);
	return this;
}