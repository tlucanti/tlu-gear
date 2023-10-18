
#include <utest/utest.h>
#include <core/color.h>
#include <core/panic.h>
#include <core/compiler.h>
#include <core/math.h>

#include <sys/types.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <inttypes.h>
#include <setjmp.h>
#include <signal.h>

static struct __utest utest_init __UTEST_ATTR = { .name = NULL,
						  .func = NULL,
						  .magic = __UTEST_MAGIC,
						  .skip = false };
static struct __utest fuzz_init __FUZZ_ATTR = { .name = NULL,
						.func = NULL,
						.magic = __FUZZ_MAGIC,
						.skip = false };

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
#define print_blue(format, ...) print_color(ANSI_BLUE, format, ##__VA_ARGS__)

void utest_ok(void)
{
	print_green("[ OK ] ");
	fflush(stdout);
}

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
		print_red("PANIC\n");
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
	int i = 1;

	const int nr_test = end - begin;

	if (CONFIG_UTEST_CATCH_SEGFAULT) {
		signal(SIGSEGV, signal_handler);
		signal(SIGBUS, signal_handler);
		signal(SIGABRT, signal_handler);
	}

	for (; begin != end; ++begin, ++i) {
		if (begin->name == NULL) {
			continue;
		}

		if (CONFIG_UTEST_CATCH_SEGFAULT && setjmp(jump_buf)) {
			continue;
		}
		printf("%s %d/%d: %s: ", name, i, nr_test, begin->name);
		fflush(stdout);

		if (begin->skip) {
			print_yellow("[SKIPPED]\n");
		} else {
			begin->func();
			utest_ok();
			printf("\n");
		}
	}
}

void unittest(void)
{
	suite_run(&utest_init, "TEST");
	suite_run(&fuzz_init, "FUZZ");
}

__cold __noret
static void test_failed(const char *file, unsigned long line)
{
	printf("\n[ASSERT FAILED]: %s:%lu\n", file, line);
	fflush(stdout);
	longjmp(jump_buf, 1);
	__unreachable();
}

static void print_bool(bool v)
{
	if (v == true) {
		print_blue("true");
	} else {
		print_blue("false");
	}
}

static void print_int(intmax_t v)
{
	if (v == 0) {
		print_blue("zero");
	} else {
		print_blue("%" PRIdMAX, v);
	}
}

static void print_ptr(const void *v)
{
	if (v == NULL) {
		print_blue("NULL");
	} else {
		print_blue("%p", v);
	}
}

static void print_sign(intmax_t v)
{
	if (v > 0) {
		print_blue("positive value");
	} else if (v < 0) {
		print_blue("negative value");
	} else {
		print_blue("zero");
	}
}

void __assert_fail_impl(const char *file, unsigned long line)
{
	print_red("[FAIL]\n");
	print_yellow("should not be here");
	test_failed(file, line);
}

void __assert_bool_impl(bool exp, bool real, const char *file, unsigned long line)
{
	if (unlikely(exp != real)) {
		print_red("[FAIL]\n");
		print_yellow("expected ");
		print_bool(exp);
		print_yellow(", got ");
		print_bool(real);
	} else {
		return;
	}

	test_failed(file, line);
}

void __assert_eq_impl(intmax_t exp, intmax_t real, bool eq, const char *file, unsigned long line)
{
	if (unlikely(eq && exp != real)) {
		print_red("[FAIL]\n");
		print_yellow("expected ");
		print_int(exp);
		print_yellow(", got ");
		print_int(real);
	} else if (unlikely(!eq && exp == real)) {
		print_red("[FAIL]\n");
		print_yellow("got ");
		print_int(real);
		print_yellow(", but didnt expect");
	} else {
		return;
	}

	test_failed(file, line);
}

void __assert_ptr_impl(const void *exp, const void *real, bool eq, const char *file, unsigned long line)
{
	if (unlikely(eq && exp != real)) {
		print_red("[FAIL]\n");
		print_yellow("expected ");
		print_ptr(exp);
		print_yellow(", got ");
		print_ptr(real);
	} else if (unlikely(!eq && exp == real)) {
		print_red("[FAIL]\n");
		print_yellow("got ");
		print_ptr(real);
		print_yellow(", but didnt expect");
	} else {
		return;
	}

	test_failed(file, line);
}

void __assert_sign_impl(intmax_t exp, intmax_t real, bool eq, const char *file, unsigned long line)
{
	if (unlikely(eq && sign(exp) != sign(real))) {
		print_red("[FAIL]\n");
		print_yellow("expected ");
		print_sign(exp);
		print_yellow(", got ");
		print_sign(real);
	} else if (unlikely(!eq && sign(exp) == sign(real))) {
		print_red("[FAIL]\n");
		print_yellow("got ");
		print_sign(real);
		print_yellow(", but expected ");
		print_sign(exp);
	} else {
		return;
	}

	test_failed(file, line);
}

