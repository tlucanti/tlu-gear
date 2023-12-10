
#include <libc/libc.h>

size_t tlu_strlen(const char *s)
{
	return (char *)tlu_memchr(s, 0) - s;
}

