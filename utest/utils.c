
#include <core/panic.h>
#include <core/color.h>
#include <utest/utils.h>

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <limits.h>
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

void *utest_malloc(size_t size)
{
	void *p;

	p = malloc(size);
	panic_on(p == NULL, "out of memory");

	memset(p, 0xff, size);
	return p;
}

static char *merge_memory(char *s1, size_t n1, char *s2, size_t n2)
{
	char *buf = utest_malloc(n1 + n2);
	memcpy(buf, s1, n1);
	memcpy(buf + n1, s2, n2);
	return buf;
}

static char *read_buf(int fd, size_t size, ssize_t *ret)
{
	char *buf = utest_malloc(size);

	*ret = read(fd, buf, size);
	panic_on(*ret < 0, "read error");

	return buf;
}

char *utest_read_all(int fd, size_t *p_read)
{
	const size_t read_size = 1;

	size_t cur_size = 0;
	char *cur_buf = NULL;

	while (true) {
		ssize_t nr_read;
		char *next;

		next = read_buf(fd, read_size, &nr_read);
		if (nr_read == 0) {
			break;
		}

		cur_buf = merge_memory(cur_buf, cur_size, next, (size_t)nr_read);
		cur_size += (size_t)nr_read;
	}

	*p_read = cur_size;
	return cur_buf;
}


void utest_random_init(uint32_t seed)
{
	if (seed == 0) {
		srandom((unsigned int)time(NULL));
	} else {
		srandom(seed);
	}
}

uint64_t utest_random(void)
{
	uint64_t r1 = (uint64_t)random();
	uint64_t r2 = (uint64_t)random();

	return r1 | (r2 << 32u);
}

uint64_t utest_random_range(uint64_t from, uint64_t to)
{
	BUG_ON(from > to, "random invalid args");

	return utest_random() % (to - from + 1) + from;
}

void utest_progress_start(void)
{
	if (!isatty(STDOUT_FILENO)) {
		return;
	}

	printf("   ");
	fflush(stdout);
}

void utest_progress(unsigned long current, unsigned long total)
{
	static unsigned long prev = ULONG_MAX;

	BUG_ON(current >= total, "too many progress");

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

void utest_progress_done(void)
{
	if (!isatty(STDOUT_FILENO)) {
		return;
	}

	printf("\b\b\bDONE\b\b\b\b");
	fflush(stdout);
}

__printf(2, 0)
static int __utest_print_color(const char *color, const char *format, va_list ap)
{
	int ret = 0;

	if (CONFIG_COLOR_OUTPUT && isatty(STDOUT_FILENO)) {
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
