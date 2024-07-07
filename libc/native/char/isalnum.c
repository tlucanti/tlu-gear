
#include <libc/char.h>

bool tlu_isalnum(uint8 c)
{
	return tlu_isdigit(c) || tlu_isalpha(c);
}

