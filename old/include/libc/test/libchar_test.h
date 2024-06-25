
#ifndef _LIBC_TEST_LIBCHAR_TEST_H_
#define _LIBC_TEST_LIBCHAR_TEST_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

enum ctype_func {
	FUNC_ISALNUM,
	FUNC_ISALPHA,
	FUNC_ISLOWER,
	FUNC_ISUPPER,
	FUNC_ISPRINT,
	FUNC_ISPUNCT,
	FUNC_ISSPACE,
	FUNC_ISHEX,
	FUNC_TOLOWER,
	FUNC_TOUPPER,
};

struct ctype_context {
	enum ctype_func function;
	const char *name;
	unsigned char c;
	unsigned char expected;
	unsigned char real;
};

void utest_ctype_suite(struct ctype_context *context);

#endif /* _LIBC_TEST_LIBCHAR_TEST_H_ */

