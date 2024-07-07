
#include <libc/char.h>

uint8 tlu_toupper(uint8 c)
{
	if (tlu_islower(c)) {
		return (uint8)(c - ('a' - 'A'));
	} else {
		return c;
	}
}


