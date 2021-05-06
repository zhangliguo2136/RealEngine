#pragma once

#include <unordered_map>
#include "SceneParser.h"

#include "BaseSceneNode.h"
#include "BaseSceneObject.h"

#include "OpenGEX.h"

namespace RealEngine 
{
	class OgexParser :public SceneParser 
	{
	public:
		std::unique_ptr<BaseSceneNode> Parse(const std::string& buf) override;

	private:
		std::unordered_map<std::string, std::shared_ptr<BaseSceneObject>> m_SceneObjects;

	private:
		void ConvertOddlStructureToSceneNode(const ODDL::Structure &structure, 
			std::unique_ptr<BaseSceneNode>& base_node, 
			BaseSceneNode &pScene);
	};
}
