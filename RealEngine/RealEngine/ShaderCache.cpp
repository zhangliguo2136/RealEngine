#include "ShaderCache.h"

ShaderCache::ShaderCache()
{

}

ShaderCache::~ShaderCache() 
{

}

std::shared_ptr<Shader> ShaderCache::findOrCreate(std::string filename)
{
	auto iter = _shaders.find(filename);

	if (iter == _shaders.end())
	{
		// ���Խ����е���ɫ���ļ���ӳ�� ��shaderCache ��ʼ���Ǽ��غ����е���ɫ��
		std::string vsfile = "../Resource/shaders/" + filename + ".vs";
		std::string fsfile = "../Resource/shaders/" + filename + ".fs";

		auto shader = std::make_shared<Shader>(vsfile, fsfile);
		_shaders.insert(std::pair<std::string, std::shared_ptr<Shader>>(filename, shader));

		return shader;
	}
	else
	{
		return iter->second;
	}

}