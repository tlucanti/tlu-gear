
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/mem.h>

#include <string.h>
#include <stdlib.h>

UTEST(memzero_simple)
{
	char before[] = "12345";
	char after[] = "12\00045";
	const uint n = strlen(before);

	tlu_memzero(before + 2, 1);
	ASSERT_EQUAL_MEM(after, before, n);
}

UTEST(memzero_seq)
{
	const uint MAX_SIZE = 512;
	const uint MAX_OFFSET = 8;

	utest_progress_start();
	for (uint offset = 0; offset < MAX_OFFSET; offset++) {
		for (uint size = 0; size < MAX_SIZE; size++) {
			char *expected = utest_malloc(size + offset);
			char *real = utest_malloc(size + offset);

			utest_random_strings(expected + offset, real, size);
			memset(expected + offset, 0, size);
			tlu_memzero(real + offset, size);

			ASSERT_EQUAL_MEM(expected + offset, real + offset, size);

			free(expected);
			free(real);
			utest_progress2(offset, size, MAX_OFFSET, MAX_SIZE);
		}
	}
	utest_progress_done();
}

