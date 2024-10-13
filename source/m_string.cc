#include "m_misc.h"

void M_strcpy(char* dest, const char* src)
{
   while (*src)
      *dest++ = *src++;
}

void M_strncpy(char* dest, const char* src, int n)
{
   int i = 0;
   while (*src && i < n)
      *dest++ = *src++, i++;
}