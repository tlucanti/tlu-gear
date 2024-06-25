
#include <libc/lexical.h>

unsigned int unumtos(char *s, uint64_t num)
{
	return unumtos_base(s, num, 10);
}

