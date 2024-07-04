
#include <libc/string.h>
#include <libc/mem.h>

uint64 tlu_strlen(const char *s)
{
	return (uint64)tlu_memchr(s, '\0') - (uint64)s;
}

