#include "GLShaderCache.h"

#include "FileUtil.h"

GLShaderCache::GLShaderCache()
{

}

GLShaderCache::~GLShaderCache()
{

}

std::shared_ptr<GLProgram> GLShaderCache::findOrCreate(std::string filename)
{
	auto iter = _shaders.find(filename);

	if (iter == _shaders.end())
	{
		// 可以将所有的着色器文件做映射 在GLShaderCache 初始化是加载好所有的着色器
		std::string vsfile = "../Resource/shaders/GL/" + filename + ".vs";
		std::string fsfile = "../Resource/shaders/GL/" + filename + ".fs";

		auto shader = std::make_shared<GLProgram>();
		shader->AttachProgram(getFileContents(vsfile), GLShaderType::SHADER_VERTEX);
		shader->AttachProgram(getFileContents(fsfile), GLShaderType::SHADER_FRAGMENT);
		shader->LinkProgram();

		_shaders.insert(std::pair<std::string, std::shared_ptr<GLProgram>>(filename, shader));
		return shader;
	}
	else
	{
		return iter->second;
	}

}