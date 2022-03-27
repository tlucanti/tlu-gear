
#ifndef TLU_MEMORY_H
# define TLU_MEMORY_H

# include <stdlib.h>

# include "TLUdefs.h"

void *_TLUallocator(size_t size) __NOTHROW;
void _TLUdeallocator(void *ptr) __NOTHROW;

#endif
