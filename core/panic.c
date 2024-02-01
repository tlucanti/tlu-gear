
#include <unistd.h>

#include <core/compiler.h>
#include <core/panic.h>

bool silent_panic = false;

static size_t lenstr(const char *s)
{
	size_t n = 0;

	while (*s) {
		++n;
		++s;
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
		buf[i] = (unsigned char)(n % 10 + '0');
		--i;
		n /= 10;
	}

	write(2, buf + i + 1, (size_t)(24 - i));
}

void __panic_impl(const char *name, const char *file, const char *function, unsigned long line, const char *reason)
{
	if (!silent_panic) {
		putstr("\n[");
		putstr(name);
		putstr("]: ");
		putstr(file);
		putstr(":");
		putnum(line);

		if (reason != NULL) {
			putstr("\n");
			putstr(function);
			putstr(": ");
			putstr(reason);
		} else {
			putstr(" (function: ");
			putstr(function);
			putstr(")");
		}
		putstr("\n");
	}

	abort();
}

