
#include <libc/libc.h>
#include <utest/utest.h>

UTEST(bzero)
{
	tlu_bzero(NULL, -1);
}

int main()
{
	unittest();
}

