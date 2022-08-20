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
		void Tick();

		void AddPhysicsWorld(PhysicsWorld* world);

	private:

		std::vector<PhysicsWorld*> _worlds;

		// ¼ÇÂ¼Ê±¼ä´Á£¨ºÁÃë£©
		long long _lastTime = 0;
	};
}