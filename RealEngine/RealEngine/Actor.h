#pragma once
#include <string>
#include "Component.h"

class TActor
{
public:
	TActor(const std::string& Name)
		:ActorName(Name) {}

public:
	virtual void Tick(float DeltaTime) {}

private:
	std::string ActorName;

	TComponent* RootComponent = nullptr;
};
