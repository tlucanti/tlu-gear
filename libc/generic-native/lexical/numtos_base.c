
#include <libc/lexical.h>
#include <core/panic.h>
#include <core/compiler.h>

#include <stdbool.h>

static unsigned int __numtos_base(char *s, int64_t num, unsigned short base, bool upper)
{
	unsigned int ret = 0;

	panic_on(base > 32 || base == 1, "base can be from 2 to 32");

	if (unlikely(num == INT64_MIN)) {
		ret += __numtos_base(s + ret, num / base, base, upper);
		ret += __numtos_base(s + ret, -(num % base), base, upper);
		return ret;
	}

	if (num < 0) {
		*s = '-';
		++s;
		ret += 1;
		num = -num;
	}

	if (upper) {
		ret += unumtos_base_upper(s, (uint64_t)num, base);
	} else {
		ret += unumtos_base(s, (uint64_t)num, base);
	}
	return ret;
}

unsigned int numtos_base(char *s, int64_t num, unsigned short base)
{
	return __numtos_base(s, num, base, false);
}

unsigned int numtos_base_upper(char *s, int64_t num, unsigned short base)
{
	return __numtos_base(s, num, base, true);
}

