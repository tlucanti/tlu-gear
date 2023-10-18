
#include <libc/libc.h>

unsigned char tlu_tolower(unsigned char c)
{
	if (tlu_isupper(c)) {
		return c + ('a' - 'A');
	} else {
		return c;
	}
}

