
#include <libc/mem.h>

int tlu_memcmp(const void *va, const void *vb, uint64 size)
{
	const uint8 *a = va;
	const uint8 *b = vb;

	for (uint64 i = 0; i < size; ++i) {
		if (a[i] != b[i]) {
			return a[i] - b[i];
		}
	}

	return 0;
}

