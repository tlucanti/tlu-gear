
#include <libc/lexical.h>
#include <libc/mem.h>
#include <core/panic.h>

static int __unumtos_base(char *s, uintmax_t num, unsigned short base,
			  const char *digits)
{
	char tmp[sizeof(num) * 8 + 1] __aligned(8);
	int idx = ARRAY_SIZE(tmp) - 1;
	int printed = 0;

	panic_on(base > 32 || base == 1, "base can be from 2 to 32");

	if (num == 0) {
		s[0] = '0';
		s[1] = '\0';
		return 1;
	}

	tmp[idx] = '\0';
	while (num != 0) {
		BUG_ON(idx == 0, "__unumtos_base: tmp buffer is too small");

		--idx;
		++printed;
		tmp[idx] = digits[num % base];
		num /= base;
	}

	tlu_memcpy(s, tmp + idx, printed + 1);
	return printed;
}

int unumtos_base(char *s, uintmax_t num, unsigned short base)
{
	static const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

	return __unumtos_base(s, num, base, digits);
}

int unumtos_base_upper(char *s, uintmax_t num, unsigned short base)
{
	static const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	return __unumtos_base(s, num, base, digits);
}

