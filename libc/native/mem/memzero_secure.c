
#include <libc/mem.h>

void tlu_memzero_secure(void *vptr, uint64 size)
{
	tlu_memset_secure(vptr, 0, size);
}

