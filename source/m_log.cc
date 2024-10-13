#include "m_log.h"

void M_WriteLog(const char* prefix, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	printf("[%s]: ", prefix);
	vprintf(fmt, args);
	va_end(args);
}