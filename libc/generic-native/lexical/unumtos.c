
#include <libc/lexical.h>

int unumtos(char *s, uintmax_t num)
{
	return unumtos_base(s, num, 10);
}

