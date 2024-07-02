
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/mem.h>

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

UTEST(memnrchr_simple)
{
	const char s[] = "12x456x78910";
	const uint n = strlen(s);

	ASSERT_EQUAL_PTR(s + 6, tlu_memnrchr(s, 'x', n));
}

UTEST(memnrchr_simple2)
{
	const char s[] = "12345x";
	const uint n = strlen(s);

	ASSERT_EQUAL_PTR(NULL, tlu_memnrchr(s, 'x', n - 1));
}

UTEST(memnrchr_simple3)
{
	const char s[] = "x2345x";
	const uint n = strlen(s);

	ASSERT_EQUAL_PTR(s, tlu_memnrchr(s, 'x', n - 1));
}


UTEST(memnrchr_simple4)
{
	const char s[] = "x";
	ASSERT_EQUAL_PTR(NULL, tlu_memnrchr(s, 'x', 0));
}

UTEST(memnrchr_seq)
{
	const uint MAX_SIZE = 512;
	const uint MAX_OFFSET = 8;

	utest_progress_start();
	for (uint offset = 0; offset < MAX_OFFSET; offset++) {
		for (uint size = 0; size < MAX_SIZE; size++) {
			char *s = utest_malloc(size + offset);
			unsigned char c = utest_random_range('a', 'z');
			const uint n = utest_random_range(0, size);

			utest_random_string(s, size + offset);
			if (size == 0) {
				free(s);
				continue;
			} else if (memchr(s + offset, c, size) == NULL) {
				c = s[offset + utest_random_range(0, size - 1)];
			}
			PANIC_ON(memchr(s + offset, c, size) == NULL);

			const void *exp = memrchr(s + offset, c, n);
			const void *real = tlu_memnrchr(s + offset, c, n);
			ASSERT_EQUAL_PTR(exp, real);

			free(s);
			utest_progress2(offset, size, MAX_OFFSET, MAX_SIZE);
		}
	}
	utest_progress_done();
}

