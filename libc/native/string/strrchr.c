
#include <libc/string.h>

char *tlu_strrchr(const char *s, uint8 c)
{
	const char *ans = NULL;

	while (*s) {
		if (*s == c)
			ans = s;
		s++;
	}

	if (c == '\0')
		return (char *)s;
	return (char *)ans;
}

