#include "AssimpMesh.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

AssimpMesh::AssimpMesh(std::vector<AssimpVertex> vertices, std::vector<unsigned int> indices, std::vector<AssimpTexture> textures)
{
	this->_vertices = vertices;
	this->_indices = indices;
	this->_textures = textures;

	this->setupMesh();
}

AssimpMesh::~AssimpMesh()
{

}

void AssimpMesh::setupMesh()
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(AssimpVertex), _vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AssimpVertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(AssimpVertex), (void*)offsetof(AssimpVertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(AssimpVertex), (void*)offsetof(AssimpVertex, TexCoords));

	glBindVertexArray(0);
}

void AssimpMesh::draw(GLProgram &shader)
{

	// ÏêÇé¿É¼ûLearnOpenGL
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < _textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = _textures[i].TextureType;
		if (name == "Texture_Diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "Texture_Specular")
			number = std::to_string(specularNr++);
		else if (name == "Texture_Normal")
			number = std::to_string(normalNr++);
		else if (name == "Texture_Height")
			number = std::to_string(heightNr++);

		glUniform1i(glGetUniformLocation(shader.getProgramID(), (name + number).c_str()), i);

		glBindTexture(GL_TEXTURE_2D, _textures[i].ID);
	}

	// draw mesh
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}