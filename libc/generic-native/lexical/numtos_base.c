
#include <libc/lexical.h>
#include <core/panic.h>
#include <core/compiler.h>

#include <stdbool.h>

static int __numtos_base(char *s, intmax_t num, unsigned short base, bool upper)
{
	int ret = 0;

	panic_on(base > 32 || base == 1, "base can be from 2 to 32");

	if (num < 0) {
		*s = '-';
		ret += 1;

		if (upper) {
			if (num <= -base) {
				ret += unumtos_base_upper(s + ret, -(num / base), base);
			}
			ret += unumtos_base_upper(s + ret, -(num % base), base);
		} else {
			if (num <= -base) {
				ret += unumtos_base(s + ret, -(num / base), base);
			}
			ret += unumtos_base(s + ret, -(num % base), base);
		}
	} else {
		if (upper) {
			ret += unumtos_base_upper(s, num, base);
		} else {
			ret += unumtos_base(s, num, base);
		}
	}

	return ret;
}

int numtos_base(char *s, intmax_t num, unsigned short base)
{
	return __numtos_base(s, num, base, false);
}

int numtos_base_upper(char *s, intmax_t num, unsigned short base)
{
	return __numtos_base(s, num, base, true);
}

