
#ifndef _LIBC_ALLOCATOR_H_
#define _LIBC_ALLOCATOR_H_

#include <malloc.h>

static inline void *tlu_malloc(unsigned long size)
{
	return malloc(size);
}

static inline void tlu_free(void *ptr)
{
	free(ptr);
}

static inline void *tlu_aligned_alloc(unsigned long size, unsigned long alignment)
{
	void *ret;

	if (posix_memalign(&ret, alignment, size) != 0) {
		return NULL;
	}
	return ret;
}

#endif /* _LIBC_ALLOCATOR_H_ */

