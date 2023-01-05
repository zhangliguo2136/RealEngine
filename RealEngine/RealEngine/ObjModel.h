#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <array>

#include "Vector.h"
#include "ObjMesh.h"
#include "ObjMatrial.h"

class ObjModel
{
public:
	ObjModel(const std::string &filename);
	~ObjModel() {};

	void LoadModelfile(const std::string &filename);

	void LoadModelMatrial(const std::string& mtlfile);

	ObjMatrial FindMatrial(const std::string& name);

	void Draw();

public:
	std::vector<Vector3f> _positions;
	std::vector<Vector2f> _texCoords;
	std::vector<Vector3f> _normals;

public:
	std::vector<ObjMesh> _objMeshs;
	std::vector<ObjMatrial> _objMatrials;

private:
	std::string _filepath;
};