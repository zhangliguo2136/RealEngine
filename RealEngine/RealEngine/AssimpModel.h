#pragma once

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "AssimpMesh.h"
#include "Matrix.h"

class AssimpModel
{
public:
	AssimpModel(std::string filename);
	~AssimpModel();

	void draw(GLProgram& shader);

private:
	void loadModelfile(std::string filename);
	void processNode(aiNode* node, const aiScene *scene);
	AssimpMesh processMesh(aiMesh* mesh, const aiScene *scene);
	std::vector<AssimpTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string name);

private:
	std::string _filename;
	std::string _filepath;
	std::vector<AssimpMesh> _meshs;

	Matrix4 _translate;
};