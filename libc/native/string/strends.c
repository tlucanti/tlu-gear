
#include <libc/string.h>
#include <libc/mem.h>

bool tlu_strends(const char *str, const char *pattern)
{
	uint64 str_len = tlu_strlen(str);
	uint64 pattern_len = tlu_strlen(pattern);

	if (pattern_len > str_len) {
		return false;
	}
	return tlu_memeq(str + str_len - pattern_len, pattern, pattern_len + 1);
}

