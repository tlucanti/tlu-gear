
#include <utest/utest.h>
#include <stddef.h>
#include <stdio.h>

static struct __utest utest_init __UTEST_ATTR = { .name = NULL,
						  .func = NULL,
						  .magic = __UTEST_MAGIC };
static struct __utest fuzz_init __FUZZ_ATTR = { .name = NULL,
						.func = NULL,
						.magic = __FUZZ_MAGIC };

static struct __utest *get_utest_begin(struct __utest *begin)
{
	unsigned long magic = begin->magic;

	while (begin->magic == magic) {
		--begin;
	}

	return ++begin;
}

static struct __utest *get_utest_end(struct __utest *end)
{
	unsigned long magic = end->magic;

	while (end->magic == magic) {
		++end;
	}

	return end;
}

static void suite_run(struct __utest *suite, const char *name)
{
	struct __utest *begin = get_utest_begin(suite);
	struct __utest *end = get_utest_end(suite);

	for (; begin != end; ++begin) {
		if (begin->name == NULL) {
			continue;
		}

		printf("%s %s: ", name, begin->name);
		fflush(stdout);
		begin->func();
		printf("[ OK ]\n");
	}
}

void unittest(void)
{
	suite_run(&utest_init, "test");
	suite_run(&fuzz_init, "fuzzer");
}

