
#ifndef _LIBC_LIBC_TEST_UTILS_H_
#define _LIBC_LIBC_TEST_UTILS_H_

#include <stddef.h>
#include <stdbool.h>

enum suite_state_machine {
	NEXT_STATE = 1,
	NEXT_OFFSET,
	NEXT_OFFSET_OR_STATE,
	STATE_DONE,
};

void utest_print_compare(unsigned char *data, unsigned char *cmp, size_t size);
void utest_generate_memory(unsigned char *m1, unsigned char *m2, size_t size, bool printable);
int utest_validate_memory(unsigned char *expected, unsigned char *real, size_t size);
int utest_validate_memory_differ(unsigned char *expected, size_t exp_size,
				 unsigned char *real, size_t real_size);

int utest_dup(int fd);
void utest_pipe(int fd[2]);
void utest_dup_to(int from, int to);

#endif /* _LIBC_LIBC_TEST_UTILS_H_ */

