
#include <libc/mem.h>

const void *tlu_memnchr(const void *vp, unsigned char c, uint64 size)
{
	const unsigned char *p = vp;

	while (size > 0) {
		if (*p == c)
			return p;
		p++;
		size--;
	}
	return NULL;
}

