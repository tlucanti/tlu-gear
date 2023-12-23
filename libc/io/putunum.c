
#include <libc/io.h>

int putunum(uintmax_t x)
{
	return putunum_to(&tlu_stdout, x);
}

