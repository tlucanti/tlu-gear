
#include <libc/char.h>

bool tlu_isalpha(uint8 c)
{
	return tlu_islower(c) || tlu_isupper(c);
}

