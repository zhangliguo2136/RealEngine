#pragma once

#include <string>
#include <vector>

#include "Vector.h"
#include "Shader.h"

struct Vertex
{
	Vector3f Position;
	Vector3f Normal;
	Vector2f TexCoords;
};

struct Texture
{
	unsigned int ID;
	std::string TextureType;
	std::string Path;
};

class Mesh 
{
public:
	Mesh(std::vector<Vertex>, std::vector<unsigned int>, std::vector<Texture>);
	~Mesh();

	void draw(Shader& shader);
private:
	// °ó¶¨Íø¸ñ
	void setupMesh();

	unsigned int _vao, _vbo, _ebo;

private:
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
	std::vector<Texture> _textures;
};