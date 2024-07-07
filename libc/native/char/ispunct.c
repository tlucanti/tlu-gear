
#include <libc/char.h>

bool tlu_ispunct(uint8 c)
{
	return (c >= '!' && c <= '/') || (c >= ':' && c <= '@') ||
	       (c >= '[' && c <= '`') || (c >= '{' && c <= '~');
}

