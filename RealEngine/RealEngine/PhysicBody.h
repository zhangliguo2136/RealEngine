#pragma once

namespace PhysicEngine
{
	class PhysicBody
	{
	public:
		PhysicBody();
		~PhysicBody();

		void Update(float dt);
	};
}