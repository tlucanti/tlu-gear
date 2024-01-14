
#include <libc/string.h>
#include <libc/mem.h>

size_t tlu_strlen(const char *s)
{
	return (size_t)((const char *)tlu_memchr(s, 0) - s);
}

