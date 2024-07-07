
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/string.h>

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

UTEST(strrchr_simple)
{
	const char *s = "12x456x78910";

	ASSERT_EQUAL_PTR(s + 6, tlu_strrchr(s, 'x'));
}

UTEST(strrchr_simple2)
{
	const char *s = "123456";

	ASSERT_NULL(tlu_strrchr(s, 'x'));
}

UTEST(strrchr_simple3)
{
	const char *s = "1234";
	const uint n = strlen(s);

	ASSERT_EQUAL_PTR(s + n, tlu_strrchr(s, '\0'));
}

UTEST(strrchr_seq)
{
	const uint MAX_SIZE = 512;
	const uint MAX_OFFSET = 8;

	utest_progress_start();
	for (uint offset = 0; offset < MAX_OFFSET; offset++) {
		for (uint size = 0; size < MAX_SIZE; size++) {
			if (size != 0) {
				char *s = utest_malloc(size + offset + 1);
				uint8 c = utest_random_range('a', 'z');

				utest_random_string(s, size + offset);
				s[offset + size] = '\0';

				if (strrchr(s + offset, c) == NULL) {
					c = s[offset + utest_random_range(0, size - 1)];
				}
				PANIC_ON(strrchr(s + offset, c) == NULL);

				const void *exp = strrchr(s + offset, c);
				const void *real = tlu_strrchr(s + offset, c);
				ASSERT_EQUAL_PTR(exp, real);

				free(s);
			}
			{
				char *s = utest_malloc(size + offset + 1);

				utest_random_string(s, size);
				s[offset + size] = '\0';

				ASSERT_NULL(tlu_strrchr(s, '#'));
				free(s);
			}
			utest_progress2(offset, size, MAX_OFFSET, MAX_SIZE);
		}
	}
	utest_progress_done();
}

