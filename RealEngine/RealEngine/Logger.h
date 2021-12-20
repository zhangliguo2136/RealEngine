#pragma once
#include <iostream>

namespace RealEngine 
{
	#define ENGINE_DEBUG false
	#define ENGINE_WARN true

	extern const void Log(const char* str, ...);

	extern const void Warn(const char* str, ...);
}
