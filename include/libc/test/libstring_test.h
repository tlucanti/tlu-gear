
#ifndef _LIBC_TEST_LIBSTRING_TEST_H_
#define _LIBC_TEST_LIBSTRING_TEST_H_

#include <libc/test/libmem_test.h>

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

enum string_func {
	FUNC_STRLEN,
	FUNC_STRCMP,
	FUNC_STREQ,
	FUNC_STRCHR,
	FUNC_STRRCHR,
	FUNC_SSTARTSWITH,
};

#define string_context mem_context

void utest_string_suite(size_t max_size, size_t max_offset,
		     	struct string_context *context, bool printable);

#endif /* _LIBC_TEST_LIBSTRING_TEST_H_ */

