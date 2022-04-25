#pragma once
#include <vector>

#include "PhysicsWorld.h"

namespace PhysicEngine
{
	class PhysicsSystem
	{
	public:
		PhysicsSystem();
		~PhysicsSystem();

		static PhysicsSystem& getInstance()
		{
			static PhysicsSystem instance;
			return instance;
		}

		PhysicsSystem(const PhysicsSystem&) = delete;
		PhysicsSystem& operator = (const PhysicsSystem&) = delete;

	public:
		void Tick(float dt);

		void AddPhysicsWorld(PhysicsWorld* world);

	private:

		std::vector<PhysicsWorld*> _worlds;
	};
}