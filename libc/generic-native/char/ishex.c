
#include <libc/libc.h>

bool tlu_ishex(unsigned char c)
{
	return tlu_isdigit(c) || (c >= 'A' && c <= 'F') ||
	       (c >= 'a' && c <= 'f');
}

