
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/mem.h>

#include <string.h>
#include <stdlib.h>

UTEST(memcpy_simple)
{
	const char *src = "12345";
	char dst[] = "xxxxx";
	const uint n = strlen(src);

	tlu_memcpy(dst, src, n);
	ASSERT_EQUAL_MEM(src, dst, n);
}

UTEST(memcpy_seq)
{
	const uint MAX_SIZE = 512;
	const uint MAX_OFFSET = 8;

	utest_progress_start();
	for (uint offs = 0; offs < MAX_OFFSET; offs++) {
		for (uint offd = 0; offd < MAX_OFFSET; offd++) {
			for (uint size = 0; size < MAX_SIZE; size++) {
				char *dst = utest_malloc(size + offd);
				char *src = utest_malloc(size + offs);

				utest_random_string(src + offs, size);
				tlu_memcpy(dst + offd, src + offs, size);
				ASSERT_EQUAL_MEM(src + offs, dst + offd, size);

				free(dst);
				free(src);

				utest_progress3(offs, offd, size, MAX_OFFSET, MAX_OFFSET, MAX_SIZE);
				if (size > 128)
					size += utest_random_range(1, 8);
			}
		}
	}
	utest_progress_done();
}

