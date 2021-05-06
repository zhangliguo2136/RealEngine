#include "OgexParser.h"

using namespace RealEngine;

std::unique_ptr<BaseSceneNode> OgexParser::Parse(const std::string &buf)
{
	std::unique_ptr<BaseSceneNode> pScene = make_unique<BaseSceneNode>("OGEX_SCENE");

	OGEX::OpenGexDataDescription openGexDataDescription;
	
	ODDL::DataResult result = openGexDataDescription.ProcessText(buf.c_str());
	if (result == ODDL::kDataOkay) 
	{
		const ODDL::Structure* structure = openGexDataDescription.GetRootStructure()->GetFirstSubnode();
		while (structure)
		{
			ConvertOddlStructureToSceneNode(*structure, pScene->SceneGraph, *pScene);

			structure->Next();
		}
	}

	return pScene;
}

void OgexParser::ConvertOddlStructureToSceneNode(const ODDL::Structure &structure,
	std::unique_ptr<BaseSceneNode>& base_node,
	BaseSceneNode &pScene)
{
	std::unique_ptr<BaseSceneNode> node;

	switch (structure.GetStructureType())
	{
		case OGEX::kStructureNode:
			{}break;
		case OGEX::kStructureGeometryNode:
			{}break;
		case OGEX::kStructureLightNode:
			{}break;
		case OGEX::kStructureCameraNode:
			{}break;
		case OGEX::kStructureGeometryObject:
			{}break;
		case OGEX::kStructureTransform:
			{}
			return;
		default:
			return;
	};
	const ODDL::Structure* sub_strurcture = structure.GetFirstSubnode();
	while (sub_strurcture)
	{
		ConvertOddlStructureToSceneNode(*sub_strurcture, node, pScene);

		sub_strurcture = sub_strurcture->Next();
	}

	// base_node->appendChild(std::move(node));
}