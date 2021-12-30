#pragma once
#include "IBaseObject.h"
#include <string>
#include <vector>

using namespace RealEngine;

class Model : public IBaseObject
{
public:
	virtual void draw() ;
	virtual void update(float deltaTime){};
	virtual void onEnter() {};
	virtual void onExit() {};
	virtual void updateTransform(Matrix4* viewProj, Matrix4* uWorldTrans);

public:
	Model(const std::string &filename);
	~Model();

	void loadModelfile(const std::string &filename);

public:
	Matrix4* _viewProj;
	Matrix4* _uWorldTransform;

private:
	std::vector<float> _vertexBuffer;
	std::vector<int> _indexBuffer;
	std::vector<float> _normalBuffer;
};