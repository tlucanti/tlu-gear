
#include <libc/string.h>

uint64 tlu_strcnt(const char *s, uint8 c)
{
	uint64 ret = 0;

	while (*s) {
		if (*s == c)
			ret++;
		s++;
	}

	return ret;
}

