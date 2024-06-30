
#include <libc/mem.h>

void tlu_memcpy(void *vdst, const void *vsrc, uint64 size)
{
	unsigned char *dst = vdst;
	const unsigned char *src = vsrc;

	for (uint64 i = 0; i < size; ++i) {
		dst[i] = src[i];
	}
}

