#pragma once
#include "IRuntimeModule.h"

namespace RealEngine {
	class OpenglDriver :public IRuntimeModule 
	{
	public:
		OpenglDriver();
		~OpenglDriver();
	};
}