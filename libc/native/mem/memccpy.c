
#include <libc/mem.h>

void *tlu_memccpy(void *vdst, const void *vsrc, uint8 c, uint64 size)
{
	uint8 *dst = vdst;
	const uint8 *src = vsrc;

	for (uint64 i = 0; i < size; ++i) {
		dst[i] = src[i];
		if (src[i] == c)
			return &dst[i + 1];
	}
	return NULL;
}

