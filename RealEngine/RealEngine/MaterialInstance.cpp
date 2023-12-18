#include "MaterialInstance.h"

TMaterialInstance::TMaterialInstance(TMaterial* Parent, const std::string& InName)
	:Material(Parent), Name(InName)
{
	Parameters = Material->Parameters;
}

void TMaterialInstance::SetTextureParameter(const std::string& Parameter, const std::string& TextureName)
{
	auto Iter = Parameters.TextureMap.find(Parameter);

	if (Iter != Parameters.TextureMap.end())
	{
		Iter->second = TextureName;
	}
}