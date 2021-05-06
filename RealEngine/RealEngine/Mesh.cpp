#include "Mesh.h"

void Mesh::addIndexArray(IndexArray &&array)
{
	m_IndexArray.push_back(std::forward<IndexArray>(array));
}

void Mesh::addVertexArray(VertexArray &&array)
{
	m_VertexArray.push_back(std::forward<VertexArray>(array));
}