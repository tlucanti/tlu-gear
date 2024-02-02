
#include <container/cstring.h>
#include <utest/utest.h>

#include <string.h>

static void util_cstring_cmp(const struct cstring *cstring, const char *s)
{
	ASSERT_EQUAL_STR(s, cstring_data(cstring));
}

UTEST(cstring_init)
{
	struct cstring a, b;

	cstring_init(&a, "123");
	cstring_init(&b, "");

	cstring_destroy(&a);
	cstring_destroy(&b);
}

UTEST(cstring_data)
{
	struct cstring a, b;

	cstring_init(&a, "123");
	cstring_init(&b, "");

	util_cstring_cmp(&a, "123");
	util_cstring_cmp(&b, "");

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
	ASSERT_EQUAL('3', cstring_at(&a, -1));
	ASSERT_EQUAL('2', cstring_at(&a, -2));
	ASSERT_EQUAL('1', cstring_at(&a, -3));

	ASSERT_PANIC(cstring_at(&a, 3));
	ASSERT_PANIC(cstring_at(&b, 0));
	ASSERT_PANIC(cstring_at(&a, -4));
	ASSERT_PANIC(cstring_at(&b, -1));

	cstring_destroy(&a);
	cstring_destroy(&b);
}

UTEST(cstring_set)
{
	struct cstring a, b;

	cstring_init(&a, "123");
	cstring_init(&b, "");

	cstring_set(&a, 0, 'x');
	util_cstring_cmp(&a, "x23");

	cstring_set(&a, 2, 'z');
	util_cstring_cmp(&a, "x2z");

	cstring_set(&a, 1, 'y');
	util_cstring_cmp(&a, "xyz");

	cstring_set(&a, -1, '3');
	util_cstring_cmp(&a, "xy3");

	cstring_set(&a, -3, '1');
	util_cstring_cmp(&a, "1y3");

	cstring_set(&a, -2, '2');
	util_cstring_cmp(&a, "123");

	ASSERT_PANIC(cstring_set(&a, 3, 'x'));
	ASSERT_PANIC(cstring_set(&b, 0, 'x'));
	ASSERT_PANIC(cstring_set(&a, 4, 'x'));
	ASSERT_PANIC(cstring_set(&b, -1, 'x'));

	cstring_destroy(&a);
	cstring_destroy(&b);
}

UTEST(csrting_append)
{
	struct cstring a, b;
	char buf[1001] = {};

	cstring_init(&a, "123");
	cstring_init(&b, "");

	cstring_append(&a, 'x');
	util_cstring_cmp(&a, "123x");

	for (int i = 0; i < 1000; ++i) {
		buf[i] = 'x';
		cstring_append(&b, 'x');
		util_cstring_cmp(&b, buf);
	}

	cstring_destroy(&a);
	cstring_destroy(&b);
}


int main(int, const char **argv)
{
	unittest(argv);
}

