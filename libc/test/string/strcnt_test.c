
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/string.h>

#include <stdlib.h>

UTEST(strcnt_simple)
{
	const char s[] = "12x456x78910x";

	ASSERT_EQUAL(3, tlu_strcnt(s, 'x'));
}

UTEST(strcnt_seq)
{
	const uint MAX_SIZE = 512;
	const uint MAX_OFFSET = 8;

	utest_progress_start();
	for (uint offset = 0; offset < MAX_OFFSET; offset++) {
		for (uint size = 0; size < MAX_SIZE; size++) {
			char *s = utest_malloc(size + offset + 1);
			float prop = utest_random_float();
			uint cnt = 0;

			utest_random_string(s, size + offset);
			s[size + offset] = '\0';
			for (uint i = 0; i < size; i++) {
				if (utest_coin_flip(prop)) {
					s[i + offset] = '#';
					cnt++;
				}
			}

			ASSERT_EQUAL(cnt, tlu_strcnt(s + offset, '#'));

			free(s);
			utest_progress2(offset, size, MAX_OFFSET, MAX_SIZE);
		}
	}
	utest_progress_done();
}

