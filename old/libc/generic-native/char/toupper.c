
#include <libc/char.h>

unsigned char tlu_toupper(unsigned char c)
{
	if (tlu_islower(c)) {
		return (unsigned char)(c - ('a' - 'A'));
	} else {
		return c;
	}
}


