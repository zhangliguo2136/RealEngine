#pragma once
#include <string>
#include <unordered_map>

struct TShaderDefines
{
public:
	bool operator == (const TShaderDefines& Other) const;

	void SetDefine(const std::string& Name, const std::string& Definition);

public:
	std::unordered_map<std::string, std::string> DefinesMap;
};

namespace std
{
	template <>
	struct hash<TShaderDefines>
	{
		std::size_t operator()(const TShaderDefines& Defines) const
		{
			using std::size_t;
			using std::hash;
			using std::string;
			// Compute individual hash values for each string 
			// and combine them using XOR
			// and bit shifting:

			size_t HashValue = 0;
			for (const auto& Pair : Defines.DefinesMap)
			{
				HashValue ^= (hash<string>()(Pair.first) << 1);
				HashValue ^= (hash<string>()(Pair.second) << 1);
			}

			return HashValue;
		}
	};
}

struct TShaderInfo
{
	std::string ShaderName;
	std::string FileName;
	TShaderDefines ShaderDefines;
};

class TShader
{
public:
	TShader(const TShaderInfo& ShaderInfo);

	void Initialize();

	bool SetParameter(std::string ParamName);

	void BindParameters();

public:
	TShaderInfo ShaderInfo;
};