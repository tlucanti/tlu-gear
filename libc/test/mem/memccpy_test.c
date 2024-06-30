
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/mem.h>

#include <string.h>
#include <stdlib.h>

UTEST(memccpy_simple)
{
	const char *src = "12345qwerty";
	char dst[] = "xxxxxyyyyyy";
	const char *after = "12345yyyyyy";
	const uint n = strlen(src);

	tlu_memccpy(dst, src, '5', n);
	ASSERT_EQUAL_MEM(after, dst, n);
}

UTEST(memccpy_simple2)
{
	const char *src = "y";
	char dst[] = "x";

	tlu_memccpy(dst, src, 'y', 0);
	ASSERT_EQUAL_MEM("x", dst, 1);
}

UTEST(memccpy_seq)
{
	const uint MAX_SIZE = 512;
	const uint MAX_OFFSET = 8;

	utest_progress_start();
	for (uint off1 = 0; off1 < MAX_OFFSET; off1++) {
		for (uint off2 = 0; off2 < MAX_OFFSET; off2++) {
			for (uint size = 0; size < MAX_SIZE; size++) {
				char *real_dst = utest_malloc(size + off1);
				char *exp_dst = utest_malloc(size + off1);
				char *real_src = utest_malloc(size + off2);
				char *exp_src = utest_malloc(size + off2);
				unsigned char c = utest_random_range('a', 'z');

				utest_random_strings(real_src + off2, exp_src + off2, size);
				tlu_memccpy(real_dst + off1, real_src + off2, c, size);
				memccpy(exp_dst + off1, exp_src + off2, c, size);

				free(real_dst);
				free(exp_dst);
				free(real_src);
				free(exp_src);

				utest_progress3(off1, off2, size, MAX_OFFSET, MAX_OFFSET, MAX_SIZE);
				if (size > 128)
					size += utest_random_range(1, 8);
			}
		}
	}
	utest_progress_done();
}

