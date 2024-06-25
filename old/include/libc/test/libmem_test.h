
#ifndef _LIBC_TEST_LIBMEM_TEST_H_
#define _LIBC_TEST_LIBMEM_TEST_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

enum mem_func {
	FUNC_NONE = 0,
	FUNC_MEMZERO,
	FUNC_MEMSET,
	FUNC_MEMCMP,
	FUNC_MEMEQ,
	FUNC_MEMNCHR,
	FUNC_MEMNRCHR,
	FUNC_MEMCHR,
	FUNC_MEMCNT,
	FUNC_MEMCPY,
	FUNC_MEMMOVE,
};

struct mem_context {
	int function;
	int state;

	unsigned char *expected_src;
	unsigned char *expected_dst;
	unsigned char *real_src;
	unsigned char *real_dst;
	size_t size;
	size_t offset;
	size_t needle;

	unsigned char chr;
};

void utest_mem_suite(size_t max_size, size_t max_offset,
		     struct mem_context *context, bool printable);
int utest_mem_suite_run(size_t max_size, size_t max_offset,
			struct mem_context *context, bool printable,
			int (*callback)(struct mem_context *));

#endif /* _LIBC_TEST_LIBMEM_TEST_H_ */

