#pragma once

class BaseSceneNode 
{
public:
	std::unique_ptr<BaseSceneNode>& SceneGraph;
};