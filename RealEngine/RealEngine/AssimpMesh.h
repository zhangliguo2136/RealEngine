#pragma once

#include <string>
#include <vector>

#include "Vector.h"
#include "GLProgram.h"

struct AssimpVertex
{
	Vector3f Position;
	Vector3f Normal;
	Vector2f TexCoords;
};

struct AssimpTexture
{
	unsigned int ID;
	std::string TextureType;
	std::string Path;
};

class AssimpMesh
{
public:
	AssimpMesh(std::vector<AssimpVertex>, std::vector<unsigned int>, std::vector<AssimpTexture>);
	~AssimpMesh();

	void draw(GLProgram& shader);
private:
	// °ó¶¨Íø¸ñ
	void setupMesh();

	unsigned int _vao, _vbo, _ebo;

private:
	std::vector<AssimpVertex> _vertices;
	std::vector<unsigned int> _indices;
	std::vector<AssimpTexture> _textures;
};