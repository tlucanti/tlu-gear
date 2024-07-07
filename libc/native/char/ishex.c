
#include <libc/char.h>

bool tlu_ishex(uint8 c)
{
	return tlu_isdigit(c) || (c >= 'A' && c <= 'F') ||
	       (c >= 'a' && c <= 'f');
}

