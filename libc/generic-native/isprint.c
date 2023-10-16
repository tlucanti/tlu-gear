
#include <libc/libc.h>

bool tlu_isprint(unsigned char c)
{
	return c >= ' ' && c <= '~';
}

