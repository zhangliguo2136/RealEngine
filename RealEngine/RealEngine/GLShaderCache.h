#pragma once
#include <map>
#include <vector>
#include <memory>

#include "GLProgram.h"

class GLShaderCache
{
public:
	GLShaderCache();
	~GLShaderCache();

	static GLShaderCache& getInstance()
	{
		static GLShaderCache instance;
		return instance;
	}

	GLShaderCache(const GLShaderCache&) = delete;
	GLShaderCache& operator = (const GLShaderCache&) = delete;

public:
	std::shared_ptr<GLProgram> findOrCreate(std::string filename);

private:
	std::map<std::string, std::shared_ptr<GLProgram>> _shaders;
};