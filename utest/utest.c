
#include <core/color.h>
#include <core/math.h>
#include <core/types.h>
#include <utest/internal.h>
#include <utest/utest.h>
#include <utest/utils.h>

#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static struct __utest utest_init __UTEST_ATTR = { .name = NULL,
						  .func = NULL,
						  .magic = __UTEST_MAGIC,
						  .skip = false };

static jmp_buf jump_buf;
static struct timespec time_start_monotonic;
static uint nr_tests = 0;
static uint nr_ok = 0;
static uint nr_skipped = 0;
static uint nr_failed = 0;

__noret static void utest_fini(const char *color);

void utest_ok(void)
{
	utest_print_green("[ OK ] ");
	fflush(stdout);
}

static void signal_handler(int sig)
{
	switch (sig) {
	case SIGSEGV:
		nr_failed++;
		utest_print_red("[SEGMENTATION FAULT]\n");
		utest_fini(ANSI_RED);
		break;
	case SIGBUS:
		nr_failed++;
		utest_print_red("[BUS ERROR]\n");
		utest_fini(ANSI_RED);
		break;
	}
}

__no_sanitize_address
static struct __utest *get_utest_begin(struct __utest *begin)
{
	uint64 magic = begin->magic;

	while (begin->magic == magic) {
		--begin;
	}

	return ++begin;
}

__no_sanitize_address
static struct __utest *get_utest_end(struct __utest *end)
{
	uint64 magic = end->magic;

	while (end->magic == magic) {
		++end;
	}

	return end;
}

static bool do_skip_utest(const char *name, const char **keep_list)
{
	if (keep_list == NULL) {
		return false;
	}
	while (*keep_list) {
		if (!strcmp(name, *keep_list)) {
			return false;
		}
		++keep_list;
	}
	return true;
}

__noret
static void utest_fini(const char *color)
{
	struct timespec time_end_monotonic;
	struct timespec time_cpu;
	double diff;

	clock_gettime(CLOCK_MONOTONIC, &time_end_monotonic);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time_cpu);
	utest_print_color(color, "RESULTS: %u tests (%u ok, %u skipped, %u failed)\n", nr_tests, nr_ok, nr_skipped, nr_failed);

	diff = time_end_monotonic.tv_sec - time_start_monotonic.tv_sec +
		((double)time_end_monotonic.tv_nsec - time_start_monotonic.tv_nsec) * 1e-9;
	printf("user time: %.4fs, system time: %.4fs\n",
	       diff, time_cpu.tv_sec + time_cpu.tv_nsec * 1e-9);
	exit(1);
}

static void suite_run(struct __utest *suite, const char *name, const char **keep_list)
{
	struct __utest *begin = get_utest_begin(suite);
	struct __utest *end = get_utest_end(suite);
	uint i = 1;

	nr_tests = end - begin;

	if (SIG_ERR == signal(SIGSEGV, signal_handler) ||
	    SIG_ERR == signal(SIGBUS, signal_handler)) {
		utest_panic("failed to set signal handlers");
	}

	for (; begin != end; ++begin, ++i) {
		if (begin->name == NULL) {
			continue;
		}

		if (setjmp(jump_buf)) {
			continue;
		}
		printf("%s %u/%u: %s:\t", name, i, nr_tests, begin->name);
		fflush(stdout);

		if (begin->skip || do_skip_utest(begin->name, keep_list)) {
			utest_print_yellow("[SKIPPED]\n");
			nr_skipped++;
		} else {
			begin->func();
			nr_ok++;
			utest_ok();
			printf("\n");
		}
	}

	if (SIG_ERR == signal(SIGSEGV, SIG_DFL) ||
	    SIG_ERR == signal(SIGBUS, SIG_DFL)) {
		utest_panic("failed restore signal handlers");
	}
	utest_fini(ANSI_GREEN);
}

void unittest(const char **argv)
{
	if (argv == NULL || argv[1] == NULL) {
		argv = NULL;
	} else {
		argv = &argv[1];
	}

	clock_gettime(CLOCK_MONOTONIC, &time_start_monotonic);
	suite_run(&utest_init, "TEST", argv);
}

__cold __noret
static void test_failed(const char *file, uint line)
{
	nr_failed++;
	printf("\n");
	utest_print_red("[ASSERT FAILED]");
	utest_print_white(": %s:%u\n", file, line);
	fflush(stdout);
	if (CONFIG_UTEST_FIRST_FAIL) {
		utest_fini(ANSI_RED);
	} else {
		longjmp(jump_buf, 1);
	}
	unreachable();
}

static void print_bool(bool v)
{
	if (v == true) {
		utest_print_blue("true");
	} else {
		utest_print_blue("false");
	}
}

static void print_int(int64 v)
{
	if (v == 0) {
		utest_print_blue("zero");
	} else {
		utest_print_blue("%ld", v);
	}
}

static void print_ptr(const void *v)
{
	if (v == NULL) {
		utest_print_blue("NULL");
	} else {
		utest_print_blue("%p", v);
	}
}

static void print_str(const char *v)
{
	if (v == NULL) {
		utest_print_blue("(nil)");
	} else {
		utest_print_blue("\"%s\"", v);
	}
}

static void print_sign(int64 v)
{
	if (v > 0) {
		utest_print_blue("positive value");
	} else if (v < 0) {
		utest_print_blue("negative value");
	} else {
		utest_print_blue("zero");
	}
}

void __assert_fail_impl(const char *file, uint line)
{
	utest_print_red("[FAIL]\n");
	utest_print_yellow("should not be here");
	test_failed(file, line);
}

void __assert_bool_impl(bool exp, bool real, const char *file, uint line)
{
	if (unlikely(exp != real)) {
		utest_print_red("[FAIL]\n");
		utest_print_yellow("expected ");
		print_bool(exp);
		utest_print_yellow(", got ");
		print_bool(real);
	} else {
		return;
	}

	test_failed(file, line);
}

void __assert_eq_impl(int64 exp, int64 real, bool eq, const char *file, uint line)
{
	if (unlikely(eq && exp != real)) {
		utest_print_red("[FAIL]\n");
		utest_print_yellow("expected ");
		print_int(exp);
		utest_print_yellow(", got ");
		print_int(real);
	} else if (unlikely(!eq && exp == real)) {
		utest_print_red("[FAIL]\n");
		utest_print_yellow("got ");
		print_int(real);
		utest_print_yellow(", but didnt expect");
	} else {
		return;
	}

	test_failed(file, line);
}

void __assert_ptr_impl(const void *exp, const void *real, bool eq, const char *file, uint line)
{
	if (unlikely(eq && exp != real)) {
		utest_print_red("[FAIL]\n");
		utest_print_yellow("expected ");
		print_ptr(exp);
		utest_print_yellow(", got ");
		print_ptr(real);
	} else if (unlikely(!eq && exp == real)) {
		utest_print_red("[FAIL]\n");
		utest_print_yellow("got ");
		print_ptr(real);
		utest_print_yellow(", but didnt expect");
	} else {
		return;
	}

	test_failed(file, line);
}

void __assert_str_impl(const char *exp, const char *real, bool eq, const char *file, uint line)
{
	bool str_eq = !strcmp(exp, real);
	size_t size_exp = strlen(exp);
	size_t size_real = strlen(real);

	if (unlikely(eq && !str_eq)) {
		utest_print_red("[FAIL]\n");
		utest_print_yellow("expected: ");

		print_str(exp);
		utest_print_yellow("\ngot:      ");

		utest_print_blue("\"");
		for (size_t i = 0; i < size_real; ++i) {
			if (i >= size_exp || exp[i] != real[i]) {
				if (isalnum(real[i])) {
					utest_print_red("%c", real[i]);
				} else {
					utest_print_red(".");
				}
			} else {
				utest_print_blue("%c", real[i]);
			}
		}
		utest_print_blue("\"");
		printf("\n");
	} else if (unlikely(!eq && str_eq)) {
		utest_print_red("[FAIL]\n");
		utest_print_yellow("got ");
		print_str(real);
		utest_print_yellow(", but didnt expect");
	} else {
		return;
	}

	test_failed(file, line);
}

void __assert_sign_impl(int64 exp, int64 real, bool eq, const char *file, uint line)
{
	if (unlikely(eq && sign(exp) != sign(real))) {
		utest_print_red("[FAIL]\n");
		utest_print_yellow("expected ");
		print_sign(exp);
		utest_print_yellow(", got ");
		print_sign(real);
	} else if (unlikely(!eq && sign(exp) == sign(real))) {
		utest_print_red("[FAIL]\n");
		utest_print_yellow("got ");
		print_sign(real);
		utest_print_yellow(", but expected ");
		print_sign(exp);
	} else {
		return;
	}

	test_failed(file, line);
}

extern __printf(2, 0)
int __utest_print_color(const char *color, const char *format, va_list ap);

__cold __noret __printf(1, 5) void
__utest_panic(const char *format, const char *file, const char *func, uint line, ...)
{
	va_list args;

	utest_print_red("[PANIC]\n");
	utest_print_white("%s:%u: %s: ", file, line, func);
	printf(ANSI_WHITE);

	va_start(args, line);
	__utest_print_color(ANSI_WHITE, format, args);
	printf("\n");
	fflush(stdout);

	nr_failed++;
	utest_fini(ANSI_RED);
}
