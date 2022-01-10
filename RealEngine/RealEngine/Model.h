#pragma once

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Matrix.h"

class Model
{
public:
	Model(std::string filename);
	~Model();

	void draw(Shader& shader);

private:
	void loadModelfile(std::string filename);
	void processNode(aiNode* node, const aiScene *scene);
	Mesh processMesh(aiMesh* mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string name);

private:
	std::string _filename;
	std::string _filepath;
	std::vector<Mesh> _meshs;

	Matrix4 _translate;
};