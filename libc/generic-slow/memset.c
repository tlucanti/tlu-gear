
#include <stddef.h>

void memset_impl(void *vptr, unsigned char c, size_t size)
{
	unsigned char *ptr = vptr;

	for (size_t i = 0; i < size; ++i) {
		ptr[i] = c;
	}
}
