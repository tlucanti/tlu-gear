
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/mem.h>

#include <string.h>
#include <stdlib.h>

UTEST(memzero_secure_simple)
{
	char before[] = "12345";
	char after[] = "12\00045";

	tlu_memzero_secure(before + 2, 1);
	ASSERT_EQUAL_STR(after, before);
}

UTEST(memzero_secure_seq)
{
	const unsigned MAX_SIZE = 512;
	const unsigned MAX_OFFSET = 8;

	utest_progress_start();
	for (unsigned offset = 0; offset < MAX_OFFSET; offset++) {
		for (unsigned size = 0; size < MAX_SIZE; size++) {
			char *expected = utest_malloc(size + offset);
			char *real = utest_malloc(size + offset);

			utest_random_strings(expected, real, size + offset);
			memset(real + offset, 0, size);
			tlu_memzero_secure(real + offset, size);

			free(expected);
			free(real);
			utest_progress(offset * MAX_OFFSET + size, MAX_OFFSET * MAX_SIZE);
		}
	}
	utest_progress_done();
}

