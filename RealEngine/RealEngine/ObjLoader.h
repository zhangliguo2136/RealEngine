#pragma once
#include <string>

#include "Mesh.h"

class TObjLoader
{
public:
	bool LoadObjMesh(std::string ObjName, TMesh& Mesh);
};