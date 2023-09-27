
#include <stddef.h>

void tlu_bzero(void *vptr, size_t size)
{
	unsigned char *ptr = vptr;

	for (size_t i = 0; i < size; ++i) {
		ptr[i] = 0u;
	}
}

