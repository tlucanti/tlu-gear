
#include <libc/mem.h>

void tlu_memset(void *vptr, uint8 c, uint64 size)
{
	uint8 *ptr = vptr;

	for (uint64 i = 0; i < size; ++i) {
		ptr[i] = c;
	}
}

