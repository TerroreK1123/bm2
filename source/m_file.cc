#include "m_misc.h"
#include "m_log.h"
#include "alloc.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>

unsigned char* M_ReadFile(const char* path)
{
   FILE* f = nullptr;
   char final_path[4096];

   sprintf(final_path, "data/%s", path);
   f = fopen(final_path, "rb");
   if (!f)
   {
      M_Error("failed to open file %s!\n", final_path);
      return NULL;
   }
   long length = 0;

   fseek(f, 0, SEEK_END);
   length = ftell(f);
   rewind(f);

   unsigned char* buffer = (unsigned char*) A_ZeroAlloc(length + 1);
   fread(buffer, 1, length, f);
   buffer[length] = '\0';
   printf("%s %i\n", buffer, length);

   return buffer;
}