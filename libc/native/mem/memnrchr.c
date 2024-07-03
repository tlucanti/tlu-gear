
#include <libc/mem.h>

const void *tlu_memnrchr(const void *vp, uint8 c, uint64 size)
{
	const uint8 *p = vp;

	p += size - 1;
	while (size > 0) {
		if (*p == c)
			return p;
		p--;
		size--;
	}
	return NULL;
}

