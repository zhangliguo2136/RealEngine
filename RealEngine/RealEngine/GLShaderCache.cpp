#include "GLShaderCache.h"

#include "FileUtil.h"
#include "GLShaderMap.h"

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
		auto shader = std::make_shared<GLProgram>();

		auto files = GLShaderMap::FilesMaps.find(filename);
		if (files != GLShaderMap::FilesMaps.end())
		{
			std::string vsfile = "../Resource/shaders/GL/" + files->second.vsfile;
			if (!files->second.vsfile.empty()) { shader->AttachProgram(getFileContents(vsfile), GLShaderType::SHADER_VERTEX); }

			std::string fsfile = "../Resource/shaders/GL/" + files->second.fsfile;
			if (!files->second.fsfile.empty()) { shader->AttachProgram(getFileContents(fsfile), GLShaderType::SHADER_FRAGMENT); }

			std::string gsfile = "../Resource/shaders/GL/" + files->second.gsfile;
			if (!files->second.gsfile.empty()) { shader->AttachProgram(getFileContents(gsfile), GLShaderType::SHADER_GEOMETRY); }

			std::string csfile = "../Resource/shaders/GL/" + files->second.csfile;
			if (!files->second.csfile.empty()) { shader->AttachProgram(getFileContents(csfile), GLShaderType::SHADER_COMPUTE); }
		}
		else
		{
			printf("GLShaderCache::findOrCreate not find shaderfile {%s} in GLFileMaps\n", filename.c_str());
		}

		// 可以将所有的着色器文件做映射 在GLShaderCache 初始化是加载好所有的着色器
		shader->LinkProgram();

		_shaders.insert(std::pair<std::string, std::shared_ptr<GLProgram>>(filename, shader));
		return shader;
	}
	else
	{
		return iter->second;
	}

}