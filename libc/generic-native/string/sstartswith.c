
#include <libc/libc.h>

bool tlu_sstartswith(const char *str, const char *pattern)
{
	while (*pattern && *str == *pattern) {
		++pattern;
		++str;
	}
	return (*pattern == '\0');
}

