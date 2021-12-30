#pragma once

#include <memory>
#include <string>

#include "IBaseObject.h"
#include "BaseSceneNode.h"

namespace RealEngine {
	class SceneParser : public IBaseObject
	{
	public:
		virtual std::unique_ptr<BaseSceneNode> Parse(const std::string &buf) = 0;
	};
}