#pragma once
#include <string>
#include <vector>
#include "Vertex.h"

class TMesh
{
public:
	using uint16 = std::uint16_t;
	using uint32 = std::uint32_t;

	TMesh();
	TMesh(TMesh&&) = default;
	TMesh(const TMesh&) = delete;
	TMesh& operator=(const TMesh&) = delete;

public:
	std::string MeshName;
	std::string InputLayoutName;

	std::vector<TMeshVertex> Vertices;
	std::vector<uint32> Indices32;
};