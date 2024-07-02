
#include <libc/mem.h>

const void *tlu_memnrchr(const void *vp, unsigned char c, uint64 size)
{
	const unsigned char *p = vp;

	p += size - 1;
	while (size > 0) {
		if (*p == c)
			return p;
		p--;
		size--;
	}
	return NULL;
}

