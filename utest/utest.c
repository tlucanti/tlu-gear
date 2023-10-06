
#include <utest/utest.h>
#include <core/color.h>

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

static struct __utest utest_init __UTEST_ATTR = { .name = NULL,
						  .func = NULL,
						  .magic = __UTEST_MAGIC };
static struct __utest fuzz_init __FUZZ_ATTR = { .name = NULL,
						.func = NULL,
						.magic = __FUZZ_MAGIC };

#define print_color(color, format, ...)                                  \
	do {                                                             \
		if (isatty(STDOUT_FILENO)) {                             \
			printf(color format ANSI_NORMAL, ##__VA_ARGS__); \
		} else {                                                 \
			printf(format, ##__VA_ARGS__);                   \
		}                                                        \
	} while (false)

#define print_green(format, ...) print_color(ANSI_BGREEN, format, ##__VA_ARGS__)
#define print_yellow(format, ...) print_color(ANSI_BYELLOW, format, ##__VA_ARGS__)
#define print_red(format, ...) print_color(ANSI_BRED, format, ##__VA_ARGS__)

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
	int i = 0;

	const int nr_test = end - begin - 1;

	for (; begin != end; ++begin) {
		if (begin->name == NULL) {
			continue;
		}

		++i;
		printf("%s %d/%d: %s: ", name, i, nr_test, begin->name);
		fflush(stdout);
		begin->func();

		print_green("[ OK ]\n");
	}
}

void unittest(void)
{
	suite_run(&utest_init, "TEST");
	suite_run(&fuzz_init, "FUZZ");
}

