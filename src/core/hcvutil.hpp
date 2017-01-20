#pragma once

#include <string>
#include <cstdarg>
namespace hcv
{
	inline std::string stringprintf(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
	}
}