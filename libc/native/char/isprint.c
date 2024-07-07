
#include <libc/char.h>

bool tlu_isprint(uint8 c)
{
	return c >= ' ' && c <= '~';
}

