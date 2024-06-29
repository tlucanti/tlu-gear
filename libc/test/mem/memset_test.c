
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/mem.h>

#include <string.h>
#include <stdlib.h>

UTEST(memset_simple)
{
	char before[] = "12345";
	char after[] = "12x45";

	tlu_memset(before + 2, 'x', 1);
	ASSERT_EQUAL_STR(after, before);
}

UTEST(memset_seq)
{
	const uint MAX_SIZE = 512;
	const uint MAX_OFFSET = 8;

	utest_progress_start();
	for (uint offset = 0; offset < MAX_OFFSET; offset++) {
		for (uint size = 0; size < MAX_SIZE; size++) {
			char *expected = utest_malloc(size + offset);
			char *real = utest_malloc(size + offset);

			utest_random_strings(expected, real, size + offset);
			memset(expected + offset, 'x', size);
			tlu_memset(real + offset, 'x', size);

			ASSERT_EQUAL_MEM(expected + offset, real + offset, size);

			free(expected);
			free(real);
			utest_progress2(offset, size, MAX_OFFSET, MAX_SIZE);
		}
	}
	utest_progress_done();
}

