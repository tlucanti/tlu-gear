
#include <libc/mem.h>

void tlu_memzero(void *vptr, uint64 size)
{
	tlu_memset(vptr, 0, size);
}

