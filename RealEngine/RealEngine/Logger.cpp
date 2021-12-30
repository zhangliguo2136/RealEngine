#include "Logger.h"
#include <stdarg.h>

const void RealEngine::Log(const char* fmt, ...)
{
	if (ENGINE_DEBUG)
	{
		printf("RealEngine[DEBUG]:  ");
		va_list args;
		va_start(args, fmt);
		vprintf(fmt, args);
		va_end(args);
	}
}

const void RealEngine::Warn(const char* fmt, ...)
{
	if (ENGINE_WARN)
	{
		printf("RealEngine[Warn]:  ");
		va_list args;
		va_start(args, fmt);
		vprintf(fmt, args);
		va_end(args);
	}
}