
#ifndef TLU_MEMORY_H
# define TLU_MEMORY_H

# include <TLUdefs.h>

# warning "remove stdlib header"
# /* remove this */ include <stdlib.h>


# ifdef __ALLOC_DEBUG
#  define __alloc_log printf
# else
#  define __alloc_log(...)
# endif /* __ALLOC_DEBUG */

void *_TLUallocator(size_t size) __ALLOCATOR;
void _TLUdeallocator(void *ptr);
void *_TLUreallocate(void *ptr, size_t new_size) __ALLOCATOR;

#endif
