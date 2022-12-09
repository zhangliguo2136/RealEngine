#pragma once
#include "GCObjectPool.h"

class NodeObject :public GCObject
{
public:
	NodeObject();
	~NodeObject() {};

public:
	GCObject* obj = nullptr;
};

NodeObject::NodeObject()
{
	obj = GCObjectPool::NewObject<GCObject>(this);
	obj->dump();
}