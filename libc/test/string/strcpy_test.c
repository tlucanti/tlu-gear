
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/string.h>

#include <stdlib.h>

UTEST(strcpy_simple)
{
	const char *src = "12345";
	char dst[] = "xxxxx";

	tlu_strcpy(dst, src);
	ASSERT_EQUAL_STR(src, dst);
}

UTEST(strcpy_seq)
{
	const uint MAX_SIZE = 512;
	const uint MAX_OFFSET = 8;

	utest_progress_start();
	for (uint offd = 0; offd < MAX_OFFSET; offd++) {
		for (uint offs = 0; offs < MAX_OFFSET; offs++) {
			for (uint size = 0; size < MAX_SIZE; size++) {
				char *dst = utest_malloc(size + offd + 1);
				char *src = utest_malloc(size + offs + 1);
				dst[size + offd] = '\0';
				src[size + offs] = '\0';

				utest_random_string(src + offs, size);
				tlu_strcpy(dst + offd, src + offs);
				ASSERT_EQUAL_STR(src + offs, dst + offd);

				free(dst);
				free(src);

				utest_progress3(offd, offs, size, MAX_OFFSET, MAX_OFFSET, MAX_SIZE);
				if (size > 128)
					size += utest_random_range(1, 8);
			}
		}
	}
	utest_progress_done();
}

