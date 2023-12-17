
#ifndef _LIBC_LIBC_TEST_UTILS_H_
#define _LIBC_LIBC_TEST_UTILS_H_

#include <stdint.h>

enum string_func {
	FUNC_NONE = 0,
	FUNC_MEMZERO,
	FUNC_MEMSET,
	FUNC_MEMCMP,
	FUNC_MEMEQ,
	FUNC_MEMNCHR,
	FUNC_MEMCHR,
	FUNC_MEMCPY,
	FUNC_MEMMOVE,

	FUNC_STRLEN,
	FUNC_STRCMP,
	FUNC_STREQ,
	FUNC_STRCHR,
	FUNC_STRRCHR,
	FUNC_SSTARTSWITH,
};

struct string_context {
	enum string_func function;
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

enum lexical_func {
	FUNC_NUMTOS,
	FUNC_UNUMTOS,
	FUNC_NUMTOS_BASE,
	FUNC_UNUMTOS_BASE,
	FUNC_NUMTOS_BASE_UPPER,
	FUNC_UNUMTOS_BASE_UPPER,
};

struct lexical_context {
	enum lexical_func function;
	int state;
	intmax_t number;
	uintmax_t unumber;
	char *expected;
	char *real;
};

void utest_string_suite(size_t max_size, size_t max_offset, struct string_context *context, bool printable);
void utest_ctype_suite(struct ctype_context *context);
void utest_lexical_suite(long max_iter, struct lexical_context *context);

#endif /* _LIBC_LIBC_TEST_UTILS_H_ */

