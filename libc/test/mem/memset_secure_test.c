
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/mem.h>

#include <string.h>
#include <stdlib.h>

UTEST(memset_secure_simple)
{
	char before[] = "12345";
	char after[] = "12x45";

	tlu_memset_secure(before + 2, 'x', 1);
	ASSERT_EQUAL_STR(after, before);
}

UTEST(memset_secure_seq)
{
	const unsigned MAX_SIZE = 512;
	const unsigned MAX_OFFSET = 8;

	utest_progress_start();
	for (unsigned offset = 0; offset < MAX_OFFSET; offset++) {
		for (unsigned size = 0; size < MAX_SIZE; size++) {
			char *expected = utest_malloc(size + offset);
			char *real = utest_malloc(size + offset);

			utest_random_strings(expected, real, size + offset);
			memset(real + offset, 'x', size);
			tlu_memset_secure(real + offset, 'x', size);

			free(expected);
			free(real);
			utest_progress(offset * MAX_OFFSET + size, MAX_OFFSET * MAX_SIZE);
		}
	}
	utest_progress_done();
}
