
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
	for (uint off1 = 0; off1 < MAX_OFFSET; off1++) {
		for (uint off2 = 0; off2 < MAX_OFFSET; off2++) {
			for (uint size = 0; size < MAX_SIZE; size++) {
				char *dst = utest_malloc(size + off1);
				char *src = utest_malloc(size + off2);

				utest_random_string(src + off2, size);
				tlu_memcpy(dst + off1, src + off2, size);

				free(dst);
				free(src);

				utest_progress3(off1, off2, size, MAX_OFFSET, MAX_OFFSET, MAX_SIZE);
				if (size > 128)
					size += utest_random_range(1, 8);
			}
		}
	}
	utest_progress_done();
}

