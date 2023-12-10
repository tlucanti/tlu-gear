
#include <libc/string.h>
#include <libc/mem.h>

size_t tlu_strlen(const char *s)
{
	return (char *)tlu_memchr(s, 0) - s;
}

