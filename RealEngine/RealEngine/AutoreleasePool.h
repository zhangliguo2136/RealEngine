#pragma once
#include <vector>
#include <string>
#include "Ref.h"

class AutoreleasePool 
{
public:
	AutoreleasePool();
	~AutoreleasePool();
	AutoreleasePool(const std::string& name);

	void addObject(Ref* object);

	void clear();

private:
	std::vector<Ref*> _managedObjectArray;
	std::string _name;
};

class PoolManager 
{
public:
	static PoolManager& getInstance() 
	{
		static PoolManager instance;
		return instance;
	};

	AutoreleasePool* getCurrentPool() const;

	friend class AutoreleasePool;

private:
	PoolManager();
	~PoolManager();

	void push(AutoreleasePool* pool);
	void pop();

	std::vector<AutoreleasePool*> _releasePoolStack;

public:
	PoolManager(const PoolManager&) = delete;
	PoolManager& operator=(const PoolManager&) = delete;
};