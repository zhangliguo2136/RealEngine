#include "ModelTest.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Shader.h"
#include "Image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


ModelTest::ModelTest(const std::string &filename)
{
	_model = Matrix4::Translate(Vector3f(0.f, 0.f, 0.f));

	loadModelfile(filename);

	// 创建顶点数组对象
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 顶点缓冲对象
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertexBuffer.size() * sizeof(VertexTest), _vertexBuffer.data(), GL_STATIC_DRAW);

	// 索引缓冲对象
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer.size() * sizeof(int), _indexBuffer.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTest), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTest), (void*)offsetof(VertexTest, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexTest), (void*)offsetof(VertexTest, TexCoords));

	glBindVertexArray(0);
}
ModelTest::~ModelTest()
{

}

void ModelTest::loadModelfile(const std::string &filename)
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

	std::vector<Vector3f> Positions;
	std::vector<Vector3f> Normals;
	std::vector<Vector2f> TexCoords;

	std::vector<std::vector<Vector3i>> Faces;

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

			Vector3f vec;
			float f;
			for (int i = 0; i < 3; ++i)
			{
				iss >> f;
				vec.values[i] = f;
			}
			Positions.push_back(vec);
		}
		else if (!line.compare(0, 2, "vt"))
		{
			iss >> trash >> trash;

			Vector2f vec;
			float f;
			for (int i = 0; i < 2; ++i)
			{
				iss >> f;
				vec.values[i] = f;
			}
			TexCoords.push_back(vec);
		}
		else if (!line.compare(0, 2, "vn"))
		{
			iss >> trash >> trash;
			float f;
			Vector3f vec;
			for (int i = 0; i < 3; ++i)
			{
				iss >> f;

				vec.values[i] = f;
			}
			Normals.push_back(vec);
		}
		/*
		"f" 表示face 三个顶点索引所构成(一个顶点索引由空间坐标 + 纹理坐标 + 法线向量)
		*/
		else if (!line.compare(0, 2, "f "))
		{
			iss >> trash;
			int f, n, uv;

			std::vector<Vector3i> face;
			for (int i = 0; i < 3; ++i)
			{
				Vector3i vec;
				iss >> f >> trash >> uv >> trash >> n;
				vec.x = f - 1;
				vec.y = n - 1;
				vec.z = uv - 1;

				face.push_back(vec);
			}
			Faces.push_back(face);
		}
	}

	printf("Positions count %d\n", Positions.size());
	printf("Normals count %d\n", Normals.size());
	printf("TexCoords count %d\n", TexCoords.size());

	for (auto face : Faces)
	{
		for (auto vec : face)
		{
			_indexBuffer.push_back(vec.x);

			VertexTest vertex;
			vertex.Position = Positions[vec.x];
			vertex.Normal = Normals[vec.y];
			vertex.TexCoords = TexCoords[vec.z];

			_vertexBuffer.push_back(vertex);
		}
	}
}

void ModelTest::draw() 
{
	Shader* shader = new Shader("../Resource/shader/ModelTest.vert", "../Resource/shader/ModelTest.frag");
	shader->useProgram();

	shader->setMatrixUniform("model", _model.data());
	shader->setMatrixUniform("view", _view.data());
	shader->setMatrixUniform("projection", _projection.data());


	glActiveTexture(GL_TEXTURE0);
	shader->setUniform1i("texture_diffuse", 0);
	glBindTexture(GL_TEXTURE_2D, Image::BindTexture("../Resource/ModelTest/diablo3_pose/diablo3_pose_diffuse.tga"));

	// 绘制网格
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, _indexBuffer.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);

	delete shader;
}