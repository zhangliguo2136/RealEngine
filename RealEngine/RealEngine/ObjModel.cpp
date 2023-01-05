#include "ObjModel.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

ObjModel::ObjModel(const std::string &filename)
{
	this->_objMatrials.resize(10);

	this->LoadModelfile(filename);
}

void ObjModel::LoadModelfile(const std::string &filename)
{
	_filepath = filename.substr(0, filename.find_last_of("/"));

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
		char trash;

		// 加载材质库
		if (!line.compare(0, 6, "mtllib"))
		{
			iss >> trash >> trash >> trash >> trash >> trash >> trash;

			std::string mtlfile;

			iss >> mtlfile;

			this->LoadModelMatrial(mtlfile);
		}

		// 加载mesh
		/*
		o 表示网格名称，意味着一个新的网格
		*/
		if (!line.compare(0, 2, "o "))
		{
			iss >> trash;

			std::string meshName;

			iss >> meshName;

			ObjMesh objMesh;
			objMesh._name = meshName;

			this->_objMeshs.push_back(objMesh);
		}


		// 填充mesh
		{
			// 设置材质名称
			/*
			o 表示网格名称，意味着一个新的网格
			*/
			if (!line.compare(0, 6, "usemtl"))
			{
				iss >> trash >> trash >> trash >> trash >> trash >> trash;

				std::string mtlname;
				iss >> mtlname;

				ObjMesh& objMesh = this->_objMeshs.back();
				objMesh._matrial = mtlname;
			}

			/*
			f 表示face 三个顶点索引所构成(一个顶点索引由空间坐标 + 纹理坐标 + 法线向量)
			*/
			if (!line.compare(0, 2, "f "))
			{
				iss >> trash;
				int f, n, uv;

				std::array<Vector3i, 3> face;
				for (int i = 0; i < 3; ++i)
				{
					iss >> f >> trash >> uv >> trash >> n;

					Vector3i vertex;
					vertex.x = f - 1;
					vertex.y = n - 1;
					vertex.z = uv - 1;
					face[i] = vertex;
				}

				ObjMesh& objMesh = this->_objMeshs.back();
				objMesh._faces.push_back(face);
			}
		}


		/*
		"v " 表示空间坐标
		*/
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

			this->_positions.push_back(vec);
		}

		/*
		vt 表示纹理坐标
		*/
		if (!line.compare(0, 2, "vt"))
		{
			iss >> trash >> trash;

			Vector2f vec;
			float f;
			for (int i = 0; i < 2; ++i)
			{
				iss >> f;
				vec.values[i] = f;
			}
			this->_texCoords.push_back(vec);
		}

		/*
		vn 表示法线向量
		*/
		if (!line.compare(0, 2, "vn"))
		{
			iss >> trash >> trash;
			float f;
			Vector3f vec;
			for (int i = 0; i < 3; ++i)
			{
				iss >> f;

				vec.values[i] = f;
			}

			this->_normals.push_back(vec);
		}
	}

	printf("Mesh Count %d\n", this->_objMeshs.size());
}


void ObjModel::LoadModelMatrial(const std::string& mtlfile)
{
	std::string filename = _filepath + "/" + mtlfile;

	std::ifstream infile(filename, std::ios_base::in);
	if (!infile.is_open())
	{
		throw std::runtime_error("Unable to open file: " + mtlfile);
	}
	std::string line;

	while (!infile.eof())
	{
		std::getline(infile, line);
		std::istringstream iss(line.c_str());
		char trash;

		// 加载材质库
		if (!line.compare(0, 6, "newmtl"))
		{
			iss >> trash >> trash >> trash >> trash >> trash >> trash;

			std::string mtlname;
			iss >> mtlname;

			ObjMatrial matrial;
			matrial._name = mtlname;

			this->_objMatrials.push_back(matrial);
		}

		if (!line.compare(0, 6, "map_Kd"))
		{
			iss >> trash >> trash >> trash >> trash >> trash >> trash;

			std::string dif_file;
			iss >> dif_file;

			TextureBuffer* diff_buf = new TextureBuffer(_filepath + "/" + dif_file);

			ObjMatrial& objMatrial = this->_objMatrials.back();
			objMatrial.diffuseTexture = diff_buf;
		}
	}

	printf("Matrial Count %d\n", this->_objMatrials .size());
}


ObjMatrial ObjModel::FindMatrial(const std::string& name)
{
	for (auto matrial : this->_objMatrials)
	{
		if (matrial._name == name)
		{
			return matrial;
		}
	}

	return ObjMatrial();
}

void ObjModel::Draw()
{

}