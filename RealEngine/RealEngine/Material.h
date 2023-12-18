#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Shader.h"
#include "Vector.h"
#include "Matrix.h"

struct TMaterialParameters
{
public:
	Vector4f DiffuseAbledo = { 1.0f, 1.0f, 1.0f, 1.0f };
	Vector3f FresnelRO = { 0.01f, 0.01f, 0.01f };
	
	float Roughness = 64.0f;

	Vector3f EmissiveColor = { 0.f, 0.f, 0.f };

	Matrix4 MatTransform = Matrix4::IdentityMatrix();

	std::unordered_map<std::string, std::string> TextureMap;
};

class TMaterial
{
public:
	TMaterial(const std::string& InName, const std::string& InShaderName);

	TShader* GetShaderByDefines(const TShaderDefines& ShaderDefines);

public:
	std::string Name;
	TMaterialParameters Parameters;

private:
	std::string ShaderName;
	std::unordered_map<TShaderDefines, std::unique_ptr<TShader>> ShaderMap;
};
