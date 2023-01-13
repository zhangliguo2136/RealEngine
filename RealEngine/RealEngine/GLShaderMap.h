#pragma once
#include <vector>
#include <map>

struct GLShaderFiles
{
	std::string vsfile;
	std::string fsfile;
	std::string gsfile;
	std::string csfile;

	GLShaderFiles(std::string vsfile, std::string fsfile, std::string gsfile, std::string csfile) :vsfile(vsfile), fsfile(fsfile), gsfile(gsfile), csfile(csfile) {}
};

#define APPEND_SHADER_FILES(file) r*r

namespace GLShaderMap
{
	std::map<std::string, GLShaderFiles> FilesMaps =
	{
		std::pair<std::string, GLShaderFiles>("Sprite",				GLShaderFiles("Sprite.vs",		"Sprite.fs",	"",		"")),
		std::pair<std::string, GLShaderFiles>("Text",				GLShaderFiles("Text.vs",		"Text.fs",		"",		"")),
		std::pair<std::string, GLShaderFiles>("ComputeParticle",	GLShaderFiles("",				"",				"",		"ComputeParticle.cs")),
		std::pair<std::string, GLShaderFiles>("ComputeParticleRender",	GLShaderFiles("ComputeParticleRender.vs", "ComputeParticleRender.fs",		"",		"")),
		std::pair<std::string, GLShaderFiles>("Model",	GLShaderFiles("Model.vs", "Model.fs",		"",		"")),
		std::pair<std::string, GLShaderFiles>("ParticlePoint_Test",	GLShaderFiles("ParticlePoint_Test.vs", "ParticlePoint_Test.fs",		"",		"")),

		std::pair<std::string, GLShaderFiles>("PathTracing",	GLShaderFiles("PathTracing.vs", "PathTracing.fs",		"",		"")),
	};
}