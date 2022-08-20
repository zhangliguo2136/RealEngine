#include "PhysicsSystem.h"

#include "TimeUtils.h"

PhysicEngine::PhysicsSystem::PhysicsSystem()
{
	_lastTime = getMillSecondTime();
}

PhysicEngine::PhysicsSystem::~PhysicsSystem()
{

}

void PhysicEngine::PhysicsSystem::AddPhysicsWorld(PhysicsWorld* world)
{
	if (world)
	{
		_worlds.push_back(world);
	}
}

void PhysicEngine::PhysicsSystem::Tick()
{
	auto currTime = getMillSecondTime();
	float deltaTime = (float)(currTime - _lastTime) / 1000.f;
	_lastTime = currTime;

	for (auto world : _worlds)
	{
		world->Tick(deltaTime);
	}
}
