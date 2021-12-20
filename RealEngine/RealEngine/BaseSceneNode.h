#pragma once
#include "BaseObject.h"
#include "SceneObjectTransfrom.h"

class BaseSceneNode: public BaseObject
{
protected:
	// 子节点
	std::list<std::unique_ptr<BaseSceneNode>> m_Childrens;
	// 变换矩阵
	std::list<std::unique_ptr<SceneObjectTransfrom>> m_Transfroms;

public:
	std::unique_ptr<BaseSceneNode> m_pSceneGraph;

public:
	BaseSceneNode() {};
	virtual ~BaseSceneNode() {};
	BaseSceneNode(std::string name) {};

	void appendChild(std::unique_ptr<BaseSceneNode>&& sub_node)
	{
		m_Childrens.push_back(std::move(sub_node));
	}
	void appendTransfrom(std::unique_ptr<SceneObjectTransfrom>&& transfrom)
	{
		m_Transfroms.push_back(std::move(transfrom));
	}
};