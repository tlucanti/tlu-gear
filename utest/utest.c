
#include <utest/utest.h>
#include <utest/utils.h>
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
#include <string.h>

static struct __utest utest_init __UTEST_ATTR = { .name = NULL,
						  .func = NULL,
						  .magic = __UTEST_MAGIC,
						  .skip = false };
static struct __utest fuzz_init __FUZZ_ATTR = { .name = NULL,
						.func = NULL,
						.magic = __FUZZ_MAGIC,
						.skip = false };

static jmp_buf jump_buf;

void utest_ok(void)
{
	utest_print_green("[ OK ] ");
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
		utest_print_red("SEGMENTATION FAULT\n");
		goto jmp;
	case SIGBUS:
		utest_print_red("BUS ERROR\n");
		goto jmp;
	case SIGABRT:
		utest_print_red("PANIC\n");
		goto jmp;
	default:
		panic("unknown error");
	}

jmp:
	longjmp(jump_buf, sig);
}

__no_sanitize_address
static struct __utest *get_utest_begin(struct __utest *begin)
{
	unsigned long magic = begin->magic;

	while (begin->magic == magic) {
		--begin;
	}

	return ++begin;
}

__no_sanitize_address
static struct __utest *get_utest_end(struct __utest *end)
{
	unsigned long magic = end->magic;

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

static void suite_run(struct __utest *suite, const char *name, const char **keep_list)
{
	struct __utest *begin = get_utest_begin(suite);
	struct __utest *end = get_utest_end(suite);
	long i = 1;

	const long nr_test = end - begin;

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
		printf("%s %ld/%ld: %s:\t", name, i, nr_test, begin->name);
		fflush(stdout);

		if (begin->skip || do_skip_utest(begin->name, keep_list)) {
			utest_print_yellow("[SKIPPED]\n");
		} else {
			begin->func();
			utest_ok();
			printf("\n");
		}
	}
}

void unittest(const char **argv)
{
	if (argv == NULL || argv[1] == NULL) {
		argv = NULL;
	} else {
		argv = &argv[1];
	}

	suite_run(&utest_init, "TEST", argv);
	suite_run(&fuzz_init, "FUZZ", argv);
}

__cold __noret
static void test_failed(const char *file, unsigned long line)
{
	printf("\n[ASSERT FAILED]: %s:%lu\n", file, line);
	fflush(stdout);
	if (CONFIG_UTEST_FIRST_FAIL) {
		abort();
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

static void print_int(intmax_t v)
{
	if (v == 0) {
		utest_print_blue("zero");
	} else {
		utest_print_blue("%" PRIdMAX, v);
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

static void print_sign(intmax_t v)
{
	if (v > 0) {
		utest_print_blue("positive value");
	} else if (v < 0) {
		utest_print_blue("negative value");
	} else {
		utest_print_blue("zero");
	}
}

void __assert_fail_impl(const char *file, unsigned long line)
{
	utest_print_red("[FAIL]\n");
	utest_print_yellow("should not be here");
	test_failed(file, line);
}

void __assert_bool_impl(bool exp, bool real, const char *file, unsigned long line)
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

void __assert_eq_impl(intmax_t exp, intmax_t real, bool eq, const char *file, unsigned long line)
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

void __assert_ptr_impl(const void *exp, const void *real, bool eq, const char *file, unsigned long line)
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

void __assert_sign_impl(intmax_t exp, intmax_t real, bool eq, const char *file, unsigned long line)
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

