
#include <libc/mem.h>

void tlu_memmove(void *vdst, const void *vsrc, uint64 size)
{
	uint8 *dst = vdst;
	const uint8 *src = vsrc;

	if (dst <= src) {
		tlu_memcpy(dst, src, size);
	} else {
		while (size) {
			size--;
			dst[size] = src[size];
		}
	}
}

