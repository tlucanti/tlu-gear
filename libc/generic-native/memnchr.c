
#include <libc/libc.h>

const void *tlu_memnchr(const void *vp, unsigned char c, size_t n)
{
	const unsigned char *p = vp;

	for (size_t i = 0; i < n; ++i) {
		if (p[i] == c) {
			return &p[i];
		}
	}
	return NULL;
}

