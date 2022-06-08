#include "PhysicsSystem.h"

PhysicEngine::PhysicsSystem::PhysicsSystem()
{

}

PhysicEngine::PhysicsSystem::~PhysicsSystem()
{

}

void PhysicEngine::PhysicsSystem::AddPhysicsWorld(PhysicsWorld* world)
{

}

void PhysicEngine::PhysicsSystem::Tick()
{
	for (auto world : _worlds)
	{
		world->Tick(0);
	}
}
