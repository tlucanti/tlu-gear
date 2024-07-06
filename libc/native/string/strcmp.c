
#include <libc/string.h>

uint64 tlu_strcmp(const char *a, const char *b)
{
	while (*a && *b) {
		if (*a != *b)
			break;
		a++;
		b++;
	}
	return *a - *b;
}

