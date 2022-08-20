#include "PhysicsWorld.h"

PhysicEngine::PhysicsWorld::PhysicsWorld()
{

}

PhysicEngine::PhysicsWorld::~PhysicsWorld()
{

}

void PhysicEngine::PhysicsWorld::Tick(float dt)
{
	for (auto body : _bodys)
	{
		body->Update(dt);
	}
}

void PhysicEngine::PhysicsWorld::AddPhysicBody(PhysicBody* body) 
{
	if (body)
	{
		_bodys.push_back(body);
	}
}