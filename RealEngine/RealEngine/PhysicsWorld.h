#pragma once
#include <vector>

#include "PhysicBody.h"
#include "Vector.h"

namespace PhysicEngine
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		~PhysicsWorld();

		void Tick(float dt);

		void AddPhysicBody(PhysicBody*);
	private:

		std::vector<PhysicBody*> _bodys;
		
		// ×÷ÓÃÁ¦
		std::vector<Vector3f> _forces;
	};
}