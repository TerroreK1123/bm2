#ifndef __M_LOG
#define __M_LOG

#include <cstdlib>
#include <cstdio>
#include <cstdarg>

void M_WriteLog(const char* prefix, const char* fmt, ...);

#define M_Info(fmt, ...) M_WriteLog("INFO", fmt, __VA_ARGS__)
#define M_Warn(fmt, ...) M_WriteLog("WARN", fmt, __VA_ARGS__)
#define M_Error(fmt, ...) M_WriteLog("ERROR", fmt, __VA_ARGS__)
#define M_Debug(fmt, ...) M_WriteLog("DEBUG", fmt, __VA_ARGS__)

#endif