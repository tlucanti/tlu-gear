
#include <libc/libc.h>

bool tlu_isalnum(unsigned char c)
{
	return tlu_isdigit(c) || tlu_isalpha(c);
}

