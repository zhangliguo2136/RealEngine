#pragma once
#include "IBaseObject.h"
#include <string>
#include <vector>
#include "Vector.h"
#include "Matrix.h"

using namespace RealEngine;

struct Vertex
{
	Vector3f Position;
	Vector3f Normal;
	Vector2f TexCoords;
};

class Model : public IBaseObject
{
public:
	virtual void draw() ;
	virtual void update(float deltaTime){};
	virtual void onEnter() {};
	virtual void onExit() {};
	virtual void updateTransform(Matrix4 view, Matrix4 projection);

public:
	Model(const std::string &filename);
	~Model();

	void loadModelfile(const std::string &filename);

public:
	Matrix4 _view;
	Matrix4 _projection;
	Matrix4 _model;

private:
	unsigned int vao, vbo, ebo;
	std::vector<Vertex> _vertexBuffer;
	std::vector<int> _indexBuffer;
};