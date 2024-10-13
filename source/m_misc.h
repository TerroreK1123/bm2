#pragma once

#include <cstdlib>
#include <cstring>

#define asizeof(arr) (sizeof(arr) / sizeof(arr[0]))

void M_strcpy(char* dest, const char* src);
void M_strncpy(char* dest, const char* src, int n);
