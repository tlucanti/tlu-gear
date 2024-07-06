
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/string.h>

#include <string.h>
#include <stdlib.h>

UTEST(strlen_simple)
{
	const char *s = "12345\0006789";

	ASSERT_EQUAL(5, tlu_strlen(s));
	ASSERT_EQUAL(0, tlu_strlen(""));
}

UTEST(strlen_simple2)
{
	const char *s = "";

	ASSERT_ZERO(tlu_strlen(s));
}

UTEST(strlen_seq)
{
	const uint MAX_SIZE = 512;
	const uint MAX_OFFSET = 8;

	utest_progress_start();
	for (uint offset = 0; offset < MAX_OFFSET; offset++) {
		for (uint size = 0; size < MAX_SIZE; size++) {
			char *s = utest_malloc(size + offset + 1);

			utest_random_string(s, size + offset);
			s[size + offset] = '\0';
			PANIC_ON(strlen(s + offset) > size);

			uint64 exp = strlen(s + offset);
			uint64 real = tlu_strlen(s + offset);
			ASSERT_EQUAL(exp, real);

			free(s);
			utest_progress2(offset, size, MAX_OFFSET, MAX_SIZE);
		}
	}
	utest_progress_done();
}

