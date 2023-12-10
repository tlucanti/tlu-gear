
#include <libc/char.h>

bool tlu_isspace(unsigned char c)
{
	return c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\r' || c == '\f';
}

