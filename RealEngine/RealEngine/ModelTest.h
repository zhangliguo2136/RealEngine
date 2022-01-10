#pragma once
#include <string>
#include <vector>
#include "Vector.h"
#include "Matrix.h"

struct VertexTest
{
	Vector3f Position;
	Vector3f Normal;
	Vector2f TexCoords;
};

class ModelTest
{
public:
	virtual void draw() ;
	virtual void update(float deltaTime){};

public:
	ModelTest(const std::string &filename);
	~ModelTest();

	void loadModelfile(const std::string &filename);

public:
	Matrix4 _view;
	Matrix4 _projection;
	Matrix4 _model;

private:
	unsigned int vao, vbo, ebo;
	std::vector<VertexTest> _vertexBuffer;
	std::vector<int> _indexBuffer;
};