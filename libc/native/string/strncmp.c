
#include <libc/string.h>

uint64 tlu_strncmp(const char *a, const char *b, uint64 n)
{
	while (*a && *b && n) {
		if (*a != *b)
			break;
		a++;
		b++;
		n--;
	}
	if (n == 0)
		return 0;
	else
		return *a - *b;
}

