
#include <libc/mem.h>

const void *tlu_memchr(const void *vp, unsigned char c)
{
	const unsigned char *p = vp;

	while (*p != c) {
		++p;
	}

	return p;
}
