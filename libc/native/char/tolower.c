
#include <libc/char.h>

uint8 tlu_tolower(uint8 c)
{
	if (tlu_isupper(c)) {
		return (uint8)(c + ('a' - 'A'));
	} else {
		return c;
	}
}

