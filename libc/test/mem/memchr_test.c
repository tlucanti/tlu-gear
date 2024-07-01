
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/mem.h>

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

UTEST(memchr_simple)
{
	const char s[] = "12x456x78910x";

	ASSERT_EQUAL_PTR(s + 2, tlu_memchr(s, 'x'));
}

UTEST(memchr_seq)
{
	const uint MAX_SIZE = 512;
	const uint MAX_OFFSET = 8;

	utest_progress_start();
	for (uint offset = 0; offset < MAX_OFFSET; offset++) {
		for (uint size = 0; size < MAX_SIZE; size++) {
			char *s = utest_malloc(size + offset);
			unsigned char c = utest_random_range('a', 'z');

			utest_random_string(s, size + offset);
			if (size == 0) {
				free(s);
				continue;
			} else if (memchr(s + offset, c, size) == NULL) {
				c = s[offset + utest_random_range(0, size - 1)];
			}
			PANIC_ON(memchr(s + offset, c, size) == NULL);

			const void *exp = rawmemchr(s + offset, c);
			const void *real = tlu_memchr(s + offset, c);
			ASSERT_EQUAL_PTR(exp, real);

			free(s);
			utest_progress2(offset, size, MAX_OFFSET, MAX_SIZE);
		}
	}
	utest_progress_done();
}

