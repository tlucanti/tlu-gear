
#include <libc/libc.h>

bool tlu_ispunct(unsigned char c)
{
	return (c >= '!' && c <= '/') || (c >= ':' && c <= '@') ||
	       (c >= '[' && c <= '`') || (c >= '{' && c <= '~');
}

