
#include <core/compiler.h>
#include <libc/mem.h>

void tlu_memset_secure(void *vptr, uint8 c, uint64 size)
{
	tlu_memset(vptr, c, size);
	barrier();
}

