#include "TimeUtils.h"

#include <chrono>

long long getMillSecondTime() 
{
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	return ms.count();
}