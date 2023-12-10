
#include <libc/libc.h>

bool tlu_streq(const char *a, const char *b)
{
	return tlu_strcmp(a, b) == 0;
}

