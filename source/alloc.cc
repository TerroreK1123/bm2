#include "alloc.h"
#include "m_log.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>

struct mem_block_s *last_diary = NULL;
bool alloc_train = false, do_alloc_debug = false;
unsigned int train_count = 0;

void *A_Alloc(long size)
{
   void *ptr = malloc(size + sizeof(struct mem_block_s));
   struct mem_block_s *block = (struct mem_block_s *)(ptr);

   if (!ptr)
   {
      M_Error("failed to allocate memory! (size %u)\n", size);
      exit(1);
   }

   memset(block, 0, sizeof(struct mem_block_s));
   block->length = (int)size;
   block->prev = last_diary;
   if (last_diary)
      last_diary->next = block;
   last_diary = block;

   if (alloc_train)
      train_count++;
   return (void *)((char*)ptr + sizeof(struct mem_block_s));
}

void *A_ZeroAlloc(long size)
{
   void *ptr = A_Alloc(size);
   memset(ptr, 0, size);
   return ptr;
}

void A_BeginAllocTrain()
{
   alloc_train = true;
}

void A_EndAllocTrain(char do_free)
{
   alloc_train = false;
   if (do_alloc_debug)
   	M_Debug("ALLOC: alloc train ended with %u allocs.\n", train_count);
   train_count = 0;

   if (do_free)
   {
      unsigned int i = 0;
      struct mem_block_s *entry = last_diary;

      while (i < train_count)
      {
         struct mem_block_s *next = entry->next, *prev = entry->prev;
         void *ptr = (char*)entry + sizeof(struct mem_block_s);
         if (do_alloc_debug)
         	A_BlockInfo(ptr);
         A_Free(ptr);

         i++;
         if (prev)
         	NEXT_BLOCK(entry, prev);
         if (next)
         	NEXT_BLOCK(entry, next);
         break;
      }
   }
   train_count = 0;
}

void A_BlockInfo(const void *ptr)
{
   struct mem_block_s *block = (struct mem_block_s *)((char*)ptr - sizeof(struct mem_block_s));
   if (do_alloc_debug)
   	M_Debug("ALLOC: next: %p, prev: %p, size: %u\n", block->next, block->prev, block->length);
}

void A_Free(const void *ptr)
{
   struct mem_block_s *block = (struct mem_block_s *)((char*)ptr - sizeof(struct mem_block_s));

   if (block->next)
      block->next->prev = block->prev;
   if (block->prev)
      block->prev->next = block->next;
   if (block == last_diary)
      last_diary = block->prev;

   free(block);
}

void A_WipeDiary(void)
{
   struct mem_block_s *entry = last_diary;
   while (entry)
   {
      struct mem_block_s *next = entry->next, *prev = entry->prev;
      void *ptr = (char*)entry + sizeof(struct mem_block_s);
      A_BlockInfo(ptr);
      A_Free(ptr);

      if (prev)
         NEXT_BLOCK(entry, prev);
      if (next)
         NEXT_BLOCK(entry, next);
      break;
   }
}
