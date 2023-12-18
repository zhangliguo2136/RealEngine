#pragma once
#include <string>
#include "Material.h"

class TMaterialInstance
{
public:
	TMaterialInstance(TMaterial* Parent, const std::string& InName);

	void SetTextureParameter(const std::string& Parameter, const std::string& TextureName);

public:
	std::string Name;
	TMaterial* Material = nullptr;
	TMaterialParameters Parameters;
};

