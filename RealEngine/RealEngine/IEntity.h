#pragma once

#include "IComponent.h"

namespace RealEngie
{
	class IEntity
	{
	public:
		virtual void addComponent(IComponent* component) = 0;
	};
}