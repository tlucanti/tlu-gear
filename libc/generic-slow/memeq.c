
#include <stddef.h>
#include <stdbool.h>

bool memeq(const void *va, const void *vb, size_t size)
{
	const unsigned char *a = va;
	const unsigned char *b = vb;

	for (size_t i = 0; i < size; ++i) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}
