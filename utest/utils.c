
#include <core/color.h>
#include <utest/utest.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define DEFINE_printf_color(__color, __format)            \
	va_list ap;                                       \
	int ret;                                          \
                                                          \
	va_start(ap, __format);                           \
	ret = __utest_print_color(__color, __format, ap); \
	va_end(ap);                                       \
	return ret;

void *utest_malloc(uint64 size)
{
	void *p;

	p = malloc(size);
	if (p == NULL)
		utest_panic("utest: out of memory");
	return p;
}

void utest_random_init(uint seed)
{
	if (seed == 0) {
		srandom((unsigned int)time(NULL));
	} else {
		srandom(seed);
	}
}

uint64 utest_random(void)
{
	uint64 r1 = (uint64)random();
	uint64 r2 = (uint64)random();

	return r1 | (r2 << 32u);
}

uint64 utest_random_range(uint64 from, uint64 to)
{
	if (from > to)
		utest_panic("utest: random invalid args");

	return utest_random() % (to - from + 1) + from;
}

void utest_random_strings(char *a, char *b, uint64 size)
{
	static const char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

	for (uint64 i = 0; i < size; i++) {
		char c = alphabet[utest_random_range(0, strlen(alphabet) - 1)];
		a[i] = c;
		b[i] = c;
	}
}

void utest_progress_start(void)
{
	if (!isatty(STDOUT_FILENO)) {
		return;
	}

	printf("   ");
	fflush(stdout);
}

void utest_progress(uint64 current, uint64 total)
{
	static uint64 prev = (uint64)-1;

	if (current >= total)
		utest_panic("too many progress: %lu out of %lu", current, total);

	if (!isatty(STDOUT_FILENO)) {
		return;
	}

	current = current * 100 / total;
	if (current != prev) {
		printf("\b\b\b%02lu%%", current);
		fflush(stdout);
		prev = current;
	}
}

void utest_progress2(uint64 inner, uint64 outer, uint64 inner_total, uint64 outer_total)
{
	utest_progress(inner * outer_total + outer, inner_total * outer_total);
}

void utest_progress3(uint64 inner, uint64 middle, uint64 outer,
		     uint64 inner_total, uint64 middle_total, uint64 outer_total)
{
	utest_progress(inner * middle_total * outer_total + middle * outer_total + outer,
		       inner_total * middle_total * outer_total);
}

void utest_progress_done(void)
{
	if (!isatty(STDOUT_FILENO)) {
		return;
	}

	printf("\b\b\bDONE\b\b\b\b");
	fflush(stdout);
}

__printf(2, 0)
int __utest_print_color(const char *color, const char *format, va_list ap)
{
	int ret = 0;

	if (CONFIG_UTEST_COLOR && isatty(STDOUT_FILENO)) {
		ret += printf("%s", color);
		ret += vprintf(format, ap);
		ret += printf("%s", ANSI_RESET);
		fflush(stdout);
	} else {
		ret += vprintf(format, ap);
	}

	return ret;
}

int utest_print_color(const char *color, const char *format, ...)
{
	va_list ap;
	int ret;

	va_start(ap, format);
	ret = __utest_print_color(color, format, ap);
	va_end(ap);
	return ret;
}

int utest_print_white(const char *format, ...)
{
	DEFINE_printf_color(ANSI_WHITE, format);
}

int utest_print_red(const char *format, ...)
{
	DEFINE_printf_color(ANSI_RED, format);
}

int utest_print_green(const char *format, ...)
{
	DEFINE_printf_color(ANSI_GREEN, format);
}

int utest_print_yellow(const char *format, ...)
{
	DEFINE_printf_color(ANSI_YELLOW, format);
}

int utest_print_blue(const char *format, ...)
{
	DEFINE_printf_color(ANSI_BLUE, format);
}

int utest_print_magenta(const char *format, ...)
{
	DEFINE_printf_color(ANSI_MAGENTA, format);
}

int utest_print_cyan(const char *format, ...)
{
	DEFINE_printf_color(ANSI_CYAN, format);
}
