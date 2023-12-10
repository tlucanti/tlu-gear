
#include <libc/char.h>

bool tlu_isalpha(unsigned char c)
{
	return tlu_islower(c) || tlu_isupper(c);
}

