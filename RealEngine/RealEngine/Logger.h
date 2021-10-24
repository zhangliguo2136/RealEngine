#pragma once
#include <iostream>

namespace RealEngine 
{
	#define ENGINE_DEBUG true
	#define ENGINE_WARN true

	extern const void Log(const char* str, ...);

	extern const void Warn(const char* str, ...);
}
