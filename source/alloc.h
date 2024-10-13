#ifndef __ALLOC
#define __ALLOC

#include <stdbool.h>

#define NEXT_BLOCK(set, val) 	\
{										\
	set = val;						\
	continue;						\
}

struct mem_block_s
{
   struct mem_block_s *next, *prev;
   int length;
};

extern 			struct mem_block_s *last_diary;
extern			bool alloc_train, do_alloc_debug;
extern 			unsigned int train_count;

void 				*A_Alloc(long size);
void 				*A_ZeroAlloc(long size);
void 				A_BeginAllocTrain();
void 				A_EndAllocTrain(char do_free);
void 				A_BlockInfo(const void *ptr);
void 				A_Free(const void *ptr);
void 				A_WipeDiary(void);

#endif
