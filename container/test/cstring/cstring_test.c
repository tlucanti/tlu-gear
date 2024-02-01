
#include <container/cstring.h>
#include <utest/utest.h>

UTEST(cstring_init)
{
	struct cstring a, b;

	cstring_init(&a, "123");
	cstring_init(&b, "");

	cstring_destroy(&a);
	cstring_destroy(&b);
}

int main(int, const char **argv)
{
	unittest(argv);
}

