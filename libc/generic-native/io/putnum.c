
#include <libc/io.h>

unsigned int putnum(int64_t x)
{
	return putnum_to(&tlu_stdout, x);
}

