
#include <libc/io.h>

int putnum(intmax_t x)
{
	return putnum_to(&tlu_stdout, x);
}

