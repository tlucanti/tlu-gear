
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
	for (uint offd = 0; offd < MAX_OFFSET; offd++) {
		for (uint offs = 0; offs < MAX_OFFSET; offs++) {
			for (uint size = 0; size < MAX_SIZE; size++) {
				char *real_dst = utest_malloc(size + offd);
				char *exp_dst = utest_malloc(size + offd);
				char *real_src = utest_malloc(size + offs);
				char *exp_src = utest_malloc(size + offs);
				uint8 c = utest_random_range('a', 'z');

				utest_random_strings(real_src + offs, exp_src + offs, size);
				tlu_memccpy(real_dst + offd, real_src + offs, c, size);
				memccpy(exp_dst + offd, exp_src + offs, c, size);

				ASSERT_EQUAL_MEM(exp_dst + offd, real_dst + offd, size);

				free(real_dst);
				free(exp_dst);
				free(real_src);
				free(exp_src);

				utest_progress3(offd, offs, size, MAX_OFFSET, MAX_OFFSET, MAX_SIZE);
				if (size > 128)
					size += utest_random_range(1, 8);
			}
		}
	}
	utest_progress_done();
}

