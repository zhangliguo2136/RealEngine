#pragma once
#include <vector>
#include <map>

struct ShaderFiles
{
	std::string vsfile;
	std::string fsfile;
	std::string gsfile;
	std::string csfile;

	ShaderFiles(std::string vsfile, std::string fsfile, std::string gsfile, std::string csfile) :vsfile(vsfile), fsfile(fsfile), gsfile(gsfile), csfile(csfile) {}
};

namespace GLShaderMap
{
	ShaderFiles Sprite = {"Sprite.vs", "Sprite.fs", "", ""};
	ShaderFiles Text = { "Text.vs", "Text.fs", "", "" };
	ShaderFiles ComputeParticle = { "", "", "", "ComputeParticle" };
}