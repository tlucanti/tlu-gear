
#include <libc/libc.h>

bool tlu_memeq(const void *va, const void *vb, size_t size)
{
	return tlu_memcmp(va, vb, size) == 0;
}
