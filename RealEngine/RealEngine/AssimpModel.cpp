#include "AssimpModel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TextureGLCache.h"
#include "TextureBufferCache.h"

AssimpModel::AssimpModel(std::string filename)
{
	_filename = filename;
	_filepath = filename.substr(0, filename.find_last_of('/'));

	_translate = Matrix4::Translate(Vector3f(0.f, 0.f, 0.f));

	this->loadModelfile(filename);
}

AssimpModel::~AssimpModel()
{

}

void AssimpModel::draw(Shader& shader)
{
	shader.setUniformMatrix4fv("model", _translate.data());

	for (auto mesh : _meshs)
	{
		mesh.draw(shader);
	}
}

void AssimpModel::loadModelfile(std::string filename)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("ERROR::ASSIMP::%s", importer.GetErrorString());
		return;
	}

	processNode(scene->mRootNode, scene);
}

void AssimpModel::processNode(aiNode* node, const aiScene *scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		_meshs.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene);
	}
}
AssimpMesh AssimpModel::processMesh(aiMesh* mesh, const aiScene *scene)
{
	std::vector<AssimpVertex> vertexs;
	std::vector<unsigned int> indices;
	std::vector<AssimpTexture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		AssimpVertex vertex;
		vertex.Position.x = mesh->mVertices[i].x;
		vertex.Position.y = mesh->mVertices[i].y;
		vertex.Position.z = mesh->mVertices[i].z;

		if (mesh->HasNormals())
		{
			vertex.Normal.x = mesh->mNormals[i].x;
			vertex.Normal.y = mesh->mNormals[i].y;
			vertex.Normal.z = mesh->mNormals[i].z;
		}

		if (mesh->mTextureCoords[0])
		{
			vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.TexCoords = Vector2f(0.0f, 0.0f);
		}

		vertexs.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; ++i) 
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// diffuse
	std::vector<AssimpTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "Texutre_Diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// spec
	std::vector<AssimpTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "Texutre_Specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// normal
	std::vector<AssimpTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "Texutre_Normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// height
	std::vector<AssimpTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "Texutre_Height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	return AssimpMesh(vertexs, indices, textures);
}

std::vector<AssimpTexture> AssimpModel::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string name)
{
	std::vector<AssimpTexture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		std::string filepath = _filepath + std::string("/") + str.C_Str();


		AssimpTexture texture;
		texture.ID = TextureGLCache::getInstance().findOrCreate(filepath)->getTextureID();
		texture.TextureType = name;
		texture.Path = str.C_Str();
		textures.push_back(texture);
	}
	return textures;
}