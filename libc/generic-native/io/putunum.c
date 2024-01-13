
#include <libc/io.h>

int putunum(uint64_t x)
{
	return putunum_to(&tlu_stdout, x);
}

