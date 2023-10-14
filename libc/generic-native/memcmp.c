
#include <stddef.h>

int memcmp(const void *va, const void *vb, size_t size)
{
	const unsigned char *a = va;
	const unsigned char *b = vb;

	for (size_t i = 0; i < size; ++i) {
		if (a[i] != b[i]) {
			return b[i] - a[i];
		}
	}
	return 0;
}
