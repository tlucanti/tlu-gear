
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

UTEST(cstring_size)
{
	struct cstring a, b;

	cstring_init(&a, "123");
	cstring_init(&b, "");

	ASSERT_EQUAL(3, cstring_size(&a));
	ASSERT_EQUAL(0, cstring_size(&b));

	cstring_destroy(&a);
	cstring_destroy(&b);
}

UTEST(cstring_at)
{
	struct cstring a, b;

	cstring_init(&a, "123");
	cstring_init(&b, "");

	ASSERT_EQUAL('1', cstring_at(&a, 0));
	ASSERT_EQUAL('2', cstring_at(&a, 1));
	ASSERT_EQUAL('3', cstring_at(&a, 2));

	ASSERT_PANIC(cstring_at(&a, 3));
	ASSERT_PANIC(cstring_at(&b, 0));

	cstring_destroy(&a);
	cstring_destroy(&b);
}


int main(int, const char **argv)
{
	unittest(argv);
}

