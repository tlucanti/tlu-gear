
#include <libc/io.h>

unsigned int putunum(uint64_t x)
{
	return putunum_to(&tlu_stdout, x);
}

