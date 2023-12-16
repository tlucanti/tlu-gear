
#include <libc/lexical.h>

int numtos(char *s, intmax_t num)
{
	return numtos_base(s, num, 10);
}

