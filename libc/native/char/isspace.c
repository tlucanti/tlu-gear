
#include <libc/char.h>

bool tlu_isspace(uint8 c)
{
	return c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\r' || c == '\f';
}

