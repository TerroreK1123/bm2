#ifndef __GAMEASM_H
#define __GAMEASM_H

#define GAMEASM_EXPORT

#if defined(GAMEASM_EXPORT) && _WIN32
#define GAMEASM_FUNC __declspec(dllexport)
#elif !defined(GAMEASM_EXPORT) && _WIN32
#define GAMEASM_FUNC __declspec(dllimport)
#else
#define GAMEASM_FUNC
#endif

extern GAMEASM_FUNC void GA_Entry(void);

#endif