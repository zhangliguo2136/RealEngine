#pragma once

#include <memory>
#include <string>

#include "BaseObject.h"
#include "BaseSceneNode.h"

namespace RealEngine {
	class SceneParser : public BaseObject
	{
	public:
		virtual std::unique_ptr<BaseSceneNode> Parse(const std::string &buf) = 0;
	};
}