
#include <libc/libc.h>
#include <stddef.h>

void tlu_bzero(void *vptr, size_t size)
{
	tlu_memset(vptr, 0, size);
}

