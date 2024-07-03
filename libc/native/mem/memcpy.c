
#include <libc/mem.h>

void tlu_memcpy(void *vdst, const void *vsrc, uint64 size)
{
	uint8 *dst = vdst;
	const uint8 *src = vsrc;

	for (uint64 i = 0; i < size; ++i) {
		dst[i] = src[i];
	}
}

