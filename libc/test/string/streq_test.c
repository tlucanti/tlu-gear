
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/string.h>

#include <stdlib.h>

UTEST(streq_simple)
{
	const char s1[] = "12345";
	const char s2[] = "12345";
	const char s3[] = "12x45";

	ASSERT_TRUE(tlu_streq(s1, s2));
	ASSERT_FALSE(tlu_streq(s1, s3));
}

UTEST(streq_simple2)
{
	const char s1[] = "";
	const char s2[] = "";

	ASSERT_TRUE(tlu_streq(s1, s2));
}

UTEST(streq_seq)
{
	const uint MAX_SIZE = 512;
	const uint MAX_OFFSET = 8;

	utest_progress_start();
	for (uint off1 = 0; off1 < MAX_OFFSET; off1++) {
		for (uint off2 = 0; off2 < MAX_OFFSET; off2++) {
			for (uint size = 0; size < MAX_SIZE; size++) {
				{
					char *s1 = utest_malloc(size + off1 + 1);
					char *s2 = utest_malloc(size + off2 + 1);
					s1[size + off1] = '\0';
					s2[size + off2] = '\0';

					utest_random_strings(s1 + off1, s2 + off2, size);
					ASSERT_TRUE(tlu_streq(s1 + off1, s2 + off2));

					free(s1);
					free(s2);
				}
				if (size != 0) {
					char *s1 = utest_malloc(size + off1 + 1);
					char *s2 = utest_malloc(size + off2 + 1);
					volatile uint diff = utest_random_range(0, size - 1);
					s1[size + off1] = '\0';
					s2[size + off2] = '\0';

					utest_random_strings(s1 + off1, s2 + off2, size);
					s1[off1 + diff] = '*';
					ASSERT_FALSE(tlu_streq(s1 + off1, s2 + off2));

					free(s1);
					free(s2);
				}
				if (size != 0) {
					char *s1 = utest_malloc(size + off1 + 1);
					char *s2 = utest_malloc(size + off2 + 1);
					volatile uint diff = utest_random_range(0, size - 1);
					s1[size + off1] = '\0';
					s2[size + off2] = '\0';

					utest_random_strings(s1 + off1, s2 + off2, size);
					s2[off2 + diff] = '*';
					ASSERT_FALSE(tlu_streq(s1 + off1, s2 + off2));

					free(s1);
					free(s2);
				}

				utest_progress3(off1, off2, size, MAX_OFFSET, MAX_OFFSET, MAX_SIZE);
				if (size > 128)
					size += utest_random_range(1, 8);
			}
		}
	}
	utest_progress_done();
}

