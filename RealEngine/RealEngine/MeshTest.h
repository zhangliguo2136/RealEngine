#pragma once
#include <vector>

// ��������
enum VertexDataType
{
	VertexDataTypeFloat = 0,
	VertexDataTypeDouble = 1
};

class VertexArray
{
protected:
	std::string m_Attribute;
	uint32_t	m_MorphTargetIndex;
	VertexDataType m_DataType;

	union {
		float* m_pDataFloat;
		double* m_pDataDouble;
	};

	size_t m_szData;
};

// ��������
enum IndexDataType
{
	IndexDataTypeFloat = 0,
	IndexDataTypeDouble = 1
};
class IndexArray
{
protected:
	uint32_t m_MaterialIndex;
	size_t	m_RestartIndex;
	IndexDataType m_DataType;

	union {
		uint16_t* m_pDataI16;
		uint32_t* m_pDataI32;
	};
};

//����
class MeshTest
{
protected:
	std::vector<IndexArray> m_IndexArray;
	std::vector<VertexArray> m_VertexArray;

	bool m_bVisible = true;
	bool m_bShadow = false;
	bool m_bMotionBlur = false;

	void addIndexArray(IndexArray &&array);
	void addVertexArray(VertexArray &&array);
};