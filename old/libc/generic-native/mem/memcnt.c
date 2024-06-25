
#include <libc/mem.h>

unsigned long tlu_memcnt(const void *vp, unsigned char c, size_t n)
{
	const unsigned char *p = vp;
	unsigned long ans = 0;

	for (size_t i = 0; i < n; ++i) {
		if (p[i] == c) {
			ans++;
		}
	}
	return ans;
}

