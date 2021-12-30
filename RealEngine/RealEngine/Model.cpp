#include "Model.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Shader.h"


Model::Model(const std::string &filename)
{
	loadModelfile(filename);
}
Model::~Model()
{

}

void Model::updateTransform(Matrix4* viewProj, Matrix4* uWorldTrans)
{
	_viewProj = viewProj;
	_uWorldTransform = uWorldTrans;
}

void Model::loadModelfile(const std::string &filename)
{
	if (!_vertexBuffer.empty())
	{
		return;
	}

	std::ifstream infile(filename, std::ios_base::in);

	if (!infile.is_open())
	{
		throw std::runtime_error("Unable to open file: " + filename);
	}

	std::string line;
	while (!infile.eof())
	{
		std::getline(infile, line);

		std::istringstream iss(line.c_str());
		/*
		"v " 表示空间坐标
		"vt" 表示纹理坐标
		"vn" 表示法线向量
		*/
		char trash;
		if (!line.compare(0, 2, "v "))
		{
			iss >> trash;
			float f;
			for (int i = 0; i < 3; ++i)
			{
				iss >> f;
				_vertexBuffer.push_back(f);
			}
		}
		else if (!line.compare(0, 2, "vt"))
		{
		}
		else if (!line.compare(0, 2, "vn"))
		{
			iss >> trash;
			float f;
			for (int i = 0; i < 3; ++i)
			{
				iss >> f;
				_normalBuffer.push_back(f);
			}
		}
		/*
		"f" 表示face 三个顶点索引所构成(一个顶点索引由空间坐标 + 纹理坐标 + 法线向量)
		*/
		else if (!line.compare(0, 2, "f "))
		{
			iss >> trash;
			int f, n, uv;
			for (int i = 0; i < 3; ++i)
			{
				iss >> f >> trash >> n >> trash >> uv;
				_indexBuffer.push_back(f);
			}
		}
	}
}

void Model::draw() 
{
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Shader* shader = new Shader("../Resource/shader/Model.vert", "../Resource/shader/Model.frag");
	shader->useProgram();

	shader->setMatrixUniform("uWorldTransform", _uWorldTransform);
	shader->setMatrixUniform("uViewProj", _viewProj);

	// 创建顶点数组对象
	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 顶点缓冲对象
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertexBuffer.size(), _vertexBuffer.data(), GL_STATIC_DRAW);

	// 索引缓冲对象
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer.size(), _indexBuffer.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(sizeof(float) * 3));

	glDrawElements(GL_TRIANGLES, _indexBuffer.size(), GL_UNSIGNED_INT, nullptr);

	delete shader;
}