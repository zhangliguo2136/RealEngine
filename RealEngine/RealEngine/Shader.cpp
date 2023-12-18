#include "Shader.h"

bool TShaderDefines::operator == (const TShaderDefines& Other) const
{
	if (DefinesMap.size() != Other.DefinesMap.size())
	{
		return false;
	}

	for (const auto& Pair : DefinesMap)
	{
		const std::string Key = Pair.first;
		const std::string Value = Pair.second;

		auto Iter = Other.DefinesMap.find(Key);
		if (Iter == Other.DefinesMap.end() || Iter->second != Value)
		{
			return false;
		}
	}

	return true;
}

void TShaderDefines::SetDefine(const std::string& Name, const std::string& Definition)
{
	DefinesMap.insert_or_assign(Name, Definition);
}


TShader::TShader(const TShaderInfo& InShaderInfo)
	:ShaderInfo(InShaderInfo)
{
	this->Initialize();
}

void TShader::Initialize()
{

}

bool TShader::SetParameter(std::string ParamName) 
{

}

void TShader::BindParameters()
{

}