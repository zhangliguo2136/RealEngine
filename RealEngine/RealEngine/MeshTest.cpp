#include "MeshTest.h"

void MeshTest::addIndexArray(IndexArray &&array)
{
	m_IndexArray.push_back(std::forward<IndexArray>(array));
}

void MeshTest::addVertexArray(VertexArray &&array)
{
	m_VertexArray.push_back(std::forward<VertexArray>(array));
}