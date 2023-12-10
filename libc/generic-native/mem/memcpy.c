
#include <libc/libc.h>

void tlu_memcpy(void *dst, const void *src, size_t size)
{
	unsigned char *d = dst;
	const unsigned char *s = src;

	while (size--) {
		*d = *s;
		++d;
		++s;
	}
}

