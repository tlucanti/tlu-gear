
#include <libc/mem.h>

void tlu_memccpy(void *vdst, const void *vsrc, unsigned char c, uint64 size)
{
	unsigned char *dst = vdst;
	const unsigned char *src = vsrc;

	for (uint64 i = 0; i < size; ++i) {
		dst[i] = src[i];
		if (src[i] == c)
			break;
	}
}

