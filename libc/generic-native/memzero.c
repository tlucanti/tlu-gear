
#include <libc/libc.h>

void tlu_memzero(void *vptr, size_t size)
{
	tlu_memset(vptr, 0, size);
}

