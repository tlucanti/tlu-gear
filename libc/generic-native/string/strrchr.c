
#include <libc/libc.h>

char *tlu_strrchr(const char *str, char c)
{
	const char *ret = NULL;

	if (*str == c) {
		ret = str;
	}

	while (*str) {
		++str;
		if (*str == c) {
			ret = str;
		}
	}

	return (char *)ret;
}

