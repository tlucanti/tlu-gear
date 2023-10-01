
#include <utest/utest.h>
#include <stddef.h>
#include <stdio.h>

static struct __utest utest_init __UTEST_ATTR = { .name = NULL,
						  .func = NULL,
						  .magic = __UTEST_MAGIC };

static struct __utest *get_utest_begin(void)
{
	struct __utest *begin = &utest_init;

	while (begin->magic == __UTEST_MAGIC) {
		--begin;
	}

	return ++begin;
}

static struct __utest *get_utest_end(void)
{
	struct __utest *end = &utest_init;

	while (end->magic == __UTEST_MAGIC) {
		++end;
	}

	return end;
}

void unittest(void)
{
	struct __utest *begin = get_utest_begin();
	struct __utest *end = get_utest_end();

	while (begin != end) {
		if (begin->name == NULL) {
			continue;
		}

		begin->func();
		printf("%s: [ OK ]\n", begin->name);
	}
}
