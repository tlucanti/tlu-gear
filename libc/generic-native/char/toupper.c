
#include <libc/char.h>

unsigned char tlu_toupper(unsigned char c)
{
	if (tlu_islower(c)) {
		return c - ('a' - 'A');
	} else {
		return c;
	}
}


