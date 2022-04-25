#pragma once

namespace PhysicEngine
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		~PhysicsWorld();

		void Tick(float dt);
	};
}