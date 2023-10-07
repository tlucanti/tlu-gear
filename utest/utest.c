
#include <utest/utest.h>
#include <core/color.h>
#include <core/panic.h>

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>

static struct __utest utest_init __UTEST_ATTR = { .name = NULL,
						  .func = NULL,
						  .magic = __UTEST_MAGIC };
static struct __utest fuzz_init __FUZZ_ATTR = { .name = NULL,
						.func = NULL,
						.magic = __FUZZ_MAGIC };

static jmp_buf jump_buf;

#define print_color(color, format, ...)                                   \
	do {                                                              \
		if (CONFIG_UTEST_COLOR_OUTPUT && isatty(STDOUT_FILENO)) { \
			printf(color format ANSI_NORMAL, ##__VA_ARGS__);  \
		} else {                                                  \
			printf(format, ##__VA_ARGS__);                    \
		}                                                         \
	} while (false)

#define print_green(format, ...) print_color(ANSI_BGREEN, format, ##__VA_ARGS__)
#define print_yellow(format, ...) print_color(ANSI_BYELLOW, format, ##__VA_ARGS__)
#define print_red(format, ...) print_color(ANSI_BRED, format, ##__VA_ARGS__)

static void signal_handler(int sig)
{
	sigset_t signal_set;

	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGSEGV);
	sigaddset(&signal_set, SIGBUS);
	sigaddset(&signal_set, SIGABRT);
	sigprocmask(SIG_UNBLOCK, &signal_set, NULL);

	switch (sig) {
	case SIGSEGV:
		print_red("SEGMENTATION FAULT\n");
		goto jmp;
	case SIGBUS:
		print_red("BUS ERROR\n");
		goto jmp;
	case SIGABRT:
		print_red("SIGABRT\n");
		goto jmp;
	default:
		panic("unknown error");
	}

jmp:
	longjmp(jump_buf, sig);
}

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

	if (CONFIG_UTEST_CATCH_SEGFAULT) {
		signal(SIGSEGV, signal_handler);
		signal(SIGBUS, signal_handler);
		signal(SIGABRT, signal_handler);
	}

	for (; begin != end; ++begin) {
		if (begin->name == NULL) {
			continue;
		}

		++i;

		if (CONFIG_UTEST_CATCH_SEGFAULT && setjmp(jump_buf)) {
			continue;
		}
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

