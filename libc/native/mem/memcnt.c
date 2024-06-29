
#include <libc/mem.h>

uint64 tlu_memcnt(const void *vp, unsigned char c, uint64 n)
{
	const unsigned char *p = vp;
	uint64 ans = 0;

	for (uint64 i = 0; i < n; ++i) {
		if (p[i] == c) {
			ans++;
		}
	}
	return ans;
}

