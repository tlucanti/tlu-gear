
#include <libc/string.h>
#include <stdio.h>

bool tlu_sendswith(const char *str, const char *pattern)
{
	size_t str_len = tlu_strlen(str);
	size_t pattern_len = tlu_strlen(pattern);
	bool retval;

	if (pattern_len > str_len) {
		return false;
	}
	retval = tlu_memeq(str + str_len - pattern_len, pattern, pattern_len + 1);
	return retval;
}

