
#include <utest/utest.h>

#include <string.h>
#include <limits.h>
#include <signal.h>

UTEST(ok)
{
	return;
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

int main()
{
	unittest();
}

