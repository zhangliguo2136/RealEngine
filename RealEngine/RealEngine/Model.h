#pragma once
#include "BaseObject.h"
#include <string>
#include <vector>

class Model : public BaseObject
{
public:
	Model(const std::string &filename);
	~Model();

	void loadModelfile(const std::string &filename);

	bool _isUpdate = false;
public:
	void updateModel();

	void draw();

private:
	std::vector<float> _vertexBuffer;
	std::vector<int> _indexBuffer;
};