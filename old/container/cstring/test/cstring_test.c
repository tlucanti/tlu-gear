
#include <core/math.h>
#include <core/panic.h>
#include <container/cstring.h>
#include <utest/utest.h>

#include <string.h>

#define type_check(type, var) (void)((type)NULL == (var))
#define util_cstring_cmp(__cstr, __s)                        \
	do {                                                 \
		type_check(const struct cstring *, __cstr);  \
		type_check(const char *, __s);               \
		ASSERT_EQUAL_STR(__s, cstring_data(__cstr)); \
	} while (false)

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

	for (unsigned long i = 0; i < ARRAY_SIZE(buf) - 1; ++i) {
		buf[i] = 'x';
		cstring_append(&b, 'x');
		util_cstring_cmp(&b, buf);
	}

	cstring_destroy(&a);
	cstring_destroy(&b);
}

UTEST(csrting_appfront)
{
	struct cstring a, b;
	char buf[1001] = {};

	memset(buf, 'x', 1000);

	cstring_init(&a, "123");
	cstring_init(&b, "");

	cstring_appfront(&a, 'x');
	util_cstring_cmp(&a, "x123");

	for (unsigned long i = 0; i < ARRAY_SIZE(buf) - 1; ++i) {
		cstring_appfront(&b, 'x');
		util_cstring_cmp(&b, buf + 999 - i);
	}

	cstring_destroy(&a);
	cstring_destroy(&b);
}

UTEST(cstring_extend)
{
	struct cstring a, b;
	const char *ext = "12345";
	char buf[1000 * 5 + 1] = {};

	cstring_init(&a, "xyz");
	cstring_init(&b, "");

	cstring_extend(&a, ext);
	util_cstring_cmp(&a, "xyz12345");

	for (int i = 0; i < 1000; ++i) {
		cstring_extend(&b, ext);
		strcat(buf, ext);
		BUG_ON(strlen(buf) >= ARRAY_SIZE(buf));
		util_cstring_cmp(&b, buf);
	}

	cstring_destroy(&a);
	cstring_destroy(&b);
}

UTEST(cstring_remove_suffix)
{
	struct cstring a, b;
	const char *ext = "12345";
	char c[2] = {};
	char bufa[1000 + 1] = {};
	char bufb[1000 * 5 + 1] = {};
	unsigned long bufa_size, bufb_size;

	cstring_init(&a, "xyz");
	cstring_init(&b, "");

	cstring_remove_suffix(&a, 1);
	util_cstring_cmp(&a, "xy");

	cstring_remove_suffix(&a, 2);
	util_cstring_cmp(&a, "");

	cstring_remove_suffix(&b, 1000);
	util_cstring_cmp(&b, "");


	for (int i = 0; i < 1000; ++i) {
		c[0] = 'a' + i % 26;

		cstring_extend(&a, c);
		strcat(bufa, c);
		BUG_ON(strlen(bufa) >= ARRAY_SIZE(bufa));

		cstring_extend(&b, ext);
		strcat(bufb, ext);
		BUG_ON(strlen(bufb) >= ARRAY_SIZE(bufb));
	}
	bufa_size = strlen(bufa);
	bufb_size = strlen(bufb);

	do {
		cstring_remove_suffix(&a, 1);
		bufa_size = max(bufa_size - 1, 0u);
		bufa[bufa_size] = '\0';
		util_cstring_cmp(&a, bufa);
	} while ((long)bufa_size >= 0);

	do {
		cstring_remove_suffix(&b, 4);
		bufb_size = max(bufb_size - 4, 0u);
		bufb[bufb_size] = '\0';
		util_cstring_cmp(&b, bufb);
	} while ((long)bufb_size >= 0);

	cstring_destroy(&a);
	cstring_destroy(&b);
}

int main(int, const char **argv)
{
	unittest(argv);
}

