#pragma once
#include <map>
#include <vector>
#include <memory>

#include "Shader.h"

class ShaderCache
{
public:
	ShaderCache();
	~ShaderCache();

	static ShaderCache& getInstance()
	{
		static ShaderCache instance;
		return instance;
	}

	ShaderCache(const ShaderCache&) = delete;
	ShaderCache& operator = (const ShaderCache&) = delete;

public:
	std::shared_ptr<Shader> findOrCreate(std::string filename);

private:
	std::map<std::string, std::shared_ptr<Shader>> _shaders;
};