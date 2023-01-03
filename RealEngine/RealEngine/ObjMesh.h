#pragma once
#include <iostream>
#include <vector>

#include "Vector.h"
#include "ObjMatrial.h"

class ObjMesh
{
public:
	// ��������
	std::string _name;

	// ����
	std::string _matrial;

public:

	std::vector<std::array<Vector3i, 3> > _faces;
};