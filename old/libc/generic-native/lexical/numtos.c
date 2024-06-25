
#include <libc/lexical.h>

unsigned int numtos(char *s, int64_t num)
{
	return numtos_base(s, num, 10);
}

