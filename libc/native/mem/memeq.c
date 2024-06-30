
#include <libc/mem.h>

int tlu_memeq(const void *va, const void *vb, uint64 size)
{
	return tlu_memcmp(va, vb, size) == 0;
}

