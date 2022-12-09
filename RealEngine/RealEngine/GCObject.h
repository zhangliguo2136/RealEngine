#pragma once
#include <iostream>

static int OBJECT_COUNT = 0;

class GCObject
{
public:
	GCObject();

	int getObjectID() 
	{
		return m_objectID;
	}

	void dump()
	{
		printf("GCObject::The Object ID is %d\n", m_objectID);
	}

public:
	static int getObjectCount()
	{
		return OBJECT_COUNT;
	};

private:
	int m_objectID = 0;
};

GCObject::GCObject()
{
	m_objectID = ++OBJECT_COUNT;
}