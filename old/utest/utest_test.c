
#include <utest/utest.h>

#include <sys/types.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <unistd.h>

UTEST(ok)
{
	return;
}

UTEST_SKIP(skip)
{
	abort();
}

UTEST(segfault)
{
	void *null = NULL;

	memset(null, 1, 1);
}

UTEST(segfault2)
{
	memset((void *)ULONG_MAX, 1, 1);
}

UTEST(segfault3)
{
	kill(getpid(), SIGSEGV);
}

UTEST(buserror)
{
	kill(getpid(), SIGBUS);
}

UTEST(abort)
{
	kill(getpid(), SIGABRT);
}

FUZZ(ok)
{
	return;
}

FUZZ_SKIP(skip)
{
	abort();
}

FUZZ(segfault)
{
	void *null = NULL;

	memset(null, 1, 1);
}

FUZZ(segfault2)
{
	memset((void *)ULONG_MAX, 1, 1);
}

FUZZ(segfault3)
{
	kill(getpid(), SIGSEGV);
}

FUZZ(buserror)
{
	kill(getpid(), SIGBUS);
}

FUZZ(abort)
{
	kill(getpid(), SIGABRT);
}

int main()
{
	unittest();
}

