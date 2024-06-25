
#include <utest/utest.h>
#include <utest/utils.h>

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

UTEST(ok)
{
	volatile int x = 0;

	utest_progress_start();
	while (x < 1e6) {
		utest_progress(x, 1e6);
		x++;
	}
	utest_progress_done();
}

UTEST_SKIP(skip)
{
	abort();
}

UTEST_SKIP(segfault)
{
	volatile int *x = 0UL;
	*x = 0;
}

UTEST_SKIP(buserror)
{
	kill(getpid(), SIGBUS);
}

UTEST(panic)
{
	utest_panic("bad");
}

int main(int argc, const char **argv)
{
	(void)argc;
	unittest(argv);
}

