
#include <libc/string.h>

unsigned long tlu_strcnt(const char *s, const char *pattern)
{
	unsigned long ans = 0;
	unsigned long plen = tlu_strlen(pattern);

	if (*pattern == '\0') {
		return tlu_strlen(s) + 1;
	}

	do {
		if (tlu_sstartswith(s, pattern)) {
			ans++;
			s += plen - 1;
		}
	} while (*s++);
	return ans;
}

