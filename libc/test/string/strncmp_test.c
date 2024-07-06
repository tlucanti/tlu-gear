
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/string.h>

#include <string.h>
#include <stdlib.h>

UTEST(strncmp_simple)
{
	const char s1[] = "12345";
	const char s2[] = "12345";
	const char s3[] = "12x45";

	ASSERT_ZERO(tlu_strncmp(s1, s2, 1000));
	ASSERT_NOT_ZERO(tlu_strncmp(s1, s3, 1000));
}

UTEST(strncmp_simple2)
{
	const char s1[] = "1234x";
	const char s2[] = "1234y";
	uint n = strlen(s1);

	ASSERT_NOT_ZERO(tlu_strncmp(s1, s2, n));
	ASSERT_ZERO(tlu_strncmp(s1, s2, n - 1));
}

UTEST(strncmp_simple3)
{
	const char s1[] = "";
	const char s2[] = "";

	ASSERT_ZERO(tlu_strncmp(s1, s2, 1000));
}

UTEST(strncmp_seq)
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
					uint64 n = size;

					s1[size + off1] = '\0';
					s2[size + off2] = '\0';
					if (utest_coin_flip(0.8))
						n = utest_random_range(0, size);

					utest_random_strings(s1 + off1, s2 + off2, size);
					int real = tlu_strncmp(s1 + off1, s2 + off2, n);
					int exp = strncmp(s1 + off1, s2 + off2, n);
					ASSERT_EQUAL_SIGN(exp, real);

					free(s1);
					free(s2);
				}
				if (size != 0) {
					char *s1 = utest_malloc(size + off1 + 1);
					char *s2 = utest_malloc(size + off2 + 1);
					volatile uint diff = utest_random_range(0, size - 1);
					uint64 n = size;

					s1[size + off1] = '\0';
					s2[size + off2] = '\0';
					if (utest_coin_flip(0.8))
						n = utest_random_range(0, size);

					utest_random_strings(s1 + off1, s2 + off2, size);
					s1[off1 + diff] = '*';
					int real = tlu_strncmp(s1 + off1, s2 + off2, n);
					int exp = strncmp(s1 + off1, s2 + off2, n);
					ASSERT_EQUAL_SIGN(exp, real);

					free(s1);
					free(s2);
				}
				if (size != 0) {
					char *s1 = utest_malloc(size + off1 + 1);
					char *s2 = utest_malloc(size + off2 + 1);
					volatile uint diff = utest_random_range(0, size - 1);
					uint64 n = size;

					s1[size + off1] = '\0';
					s2[size + off2] = '\0';
					if (utest_coin_flip(0.8))
						n = utest_random_range(0, size);

					utest_random_strings(s1 + off1, s2 + off2, size);
					s2[off2 + diff] = '*';
					int real = tlu_strncmp(s1 + off1, s2 + off2, n);
					int exp = strncmp(s1 + off1, s2 + off2, n);
					ASSERT_EQUAL_SIGN(exp, real);

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

