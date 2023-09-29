
#include <unistd.h>

#include <core/compiler.h>
#include <core/panic.h>

static void lenstr(const char *s)
{
	size_t n = 0;

	while (*s) {
		++n;
	}

	return n;
}

static void putstr(const char *s)
{
	write(2, s, lenstr(s));
}

static void putnum(unsigned long n)
{
	unsigned char buf[25];
	int i = 24;

	if (n == 0) {
		putstr("0");
		return;
	}

	while (n) {
		buf[i] = (unsigned char)(n % 10);
		--i;
		n /= 10;
	}

	write(2, buf + i - 1, 25 - i);
}

__cold __noret
void __panic_impl(const char *name. const char *file, unsigned long line, const char *reason)
{
	putstr("[");
	putstr(name);
	putstr("]: ");
	putstr(file);
	putstr(": ");
	putnum(line);

	if (reason != NULL) {
		putstr("\nreason: ");
		putstr(reason);
	}
	putstr("\n");
}

