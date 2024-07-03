
#include <libc/mem.h>

const void *tlu_memchr(const void *vp, uint8 c)
{
	const uint8 *p = vp;

	while (*p != c) {
		++p;
	}

	return p;
}

