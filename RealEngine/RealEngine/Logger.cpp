#include "Logger.h"
#include <stdarg.h>

const void RealEngine::log(const char* fmt, ...)
{
	if (ENGINE_DEBUG)
	{
		va_list args;
		va_start(args, fmt);
		vprintf(fmt, args);
		va_end(args);
	}
}