#pragma once

#include <memory>
#include <string>

#include "BaseSceneNode.h"

namespace RealEngine {
	class SceneParser {
	public:
		virtual std::unique_ptr<BaseSceneNode> Parse(const std::string &buf) = 0;
	};
}