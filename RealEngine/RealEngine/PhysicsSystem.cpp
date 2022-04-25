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

void PhysicEngine::PhysicsSystem::Tick(float dt)
{
	for (auto world : _worlds)
	{
		world->Tick(dt);
	}
}
