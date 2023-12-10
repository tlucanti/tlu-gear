
#include <libc/libc.h>

void tlu_memmove(void *dst, const void *src, size_t size)
{
	unsigned char *d = dst;
	const unsigned char *s = src;
	size_t i = size;

	if (s > d && s - d < (ptrdiff_t)size) {
		tlu_memcpy(dst, src, size);
		return;
	}

	while (i != 0) {
		--i;
		d[i] = s[i];
	}
}

