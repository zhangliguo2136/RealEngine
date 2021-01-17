#pragma once

class Ref
{
public:
	void retain();
	void release();

	// 自动释放（放入自动释放池中）
	Ref* autorelease();

	unsigned int getReferenceCount() const;
private:
	unsigned int _referenceCount;

	friend class AutoreleasePool;
};