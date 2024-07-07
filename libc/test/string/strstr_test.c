
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/string.h>

#include <stdlib.h>
#include <string.h>

UTEST(strstr_simple)
{
	const char s1[] = "12345";
	const char s2[] = "12345";
	const char s3[] = "12x45";

	ASSERT_EQUAL_PTR(s1, tlu_strstr(s1, s2));
	ASSERT_NULL(tlu_strstr(s1, s3));
}

UTEST(strstr_simple2)
{
	const char s1[] = "";
	const char s2[] = "";

	ASSERT_EQUAL_PTR(s1, tlu_strstr(s1, s2));
}

UTEST(strstr_simple3)
{
	const char s1[] = "aaaba";
	const char s2[] = "aaba";

	ASSERT_EQUAL_PTR(s1 + 1, tlu_strstr(s1, s2));
	ASSERT_NULL(tlu_strstr(s2, s1));
}

UTEST(strstr_seq)
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

					utest_random_strings(s1 + off1, s2 + off2, size);
					s1[off1 + size] = '\0';
					s2[off2 + utest_random_range(0, size)] = '\0';

					const char *real = tlu_strstr(s1 + off1, s2 + off2);
					const char *exp = strstr(s1 + off1, s2 + off2);
					ASSERT_EQUAL_PTR(exp, real);

					free(s1);
					free(s2);
				}
				if (size != 0) {
					char *s1 = utest_malloc(size + off1 + 1);
					char *s2 = utest_malloc(size + off2 + 1);

					volatile uint end = utest_random_range(1, size);
					volatile uint diff = utest_random_range(0, end - 1);
					utest_random_strings(s1 + off1, s2 + off2, size);
					s1[off1 + size] = '\0';
					s2[off2 + end] = '\0';
					s2[off2 + diff] = '*';

					const char *real = tlu_strstr(s1 + off1, s2 + off2);
					const char *exp = strstr(s1 + off1, s2 + off2);
					ASSERT_EQUAL_PTR(exp, real);

					free(s1);
					free(s2);
				}
				if (size != 0) {
					char *s1 = utest_malloc(size + off1 + 1);
					char *s2 = utest_malloc(size + off2 + 1);

					volatile uint end = utest_random_range(1, size);
					volatile uint diff = utest_random_range(0, size - 1);
					utest_random_strings(s1 + off1, s2 + off2, size);
					s1[off1 + size] = '\0';
					s1[off1 + diff] = '*';
					s2[off2 + end] = '\0';

					const char *real = tlu_strstr(s1 + off1, s2 + off2);
					const char *exp = strstr(s1 + off1, s2 + off2);
					ASSERT_EQUAL_PTR(exp, real);

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

