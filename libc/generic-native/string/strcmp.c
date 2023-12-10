
#include <libc/libc.h>

int tlu_strcmp(const char *a, const char *b)
{
	while (*a && *b && *a == *b) {
		++a;
		++b;
	}
	return (unsigned char)*a - (unsigned char)*b;
}

