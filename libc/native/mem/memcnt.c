
#include <libc/mem.h>

uint64 tlu_memcnt(const void *vp, uint8 c, uint64 n)
{
	const uint8 *p = vp;
	uint64 ans = 0;

	for (uint64 i = 0; i < n; ++i) {
		if (p[i] == c) {
			ans++;
		}
	}
	return ans;
}

