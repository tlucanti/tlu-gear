
#include <libc/string.h>

bool tlu_strstarts(const char *str, const char *pattern)
{
	while (*pattern && *str == *pattern) {
		++pattern;
		++str;
	}
	return (*pattern == '\0');
}

