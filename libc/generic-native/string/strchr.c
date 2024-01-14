
#include <libc/string.h>

const char *tlu_strchr(const char *str, char c)
{
	while (*str && *str != c) {
		++str;
	}

	if (*str == c) {
		return str;
	} else {
		return NULL;
	}
}

