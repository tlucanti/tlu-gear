
#ifndef _LIBC_TEST_LIBLEXICAL_TEST_H_
#define _LIBC_TEST_LIBLEXICAL_TEST_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

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
	int64_t number;
	uint64_t unumber;
	char *expected;
	char *real;
};

void utest_lexical_suite(unsigned long max_iter, struct lexical_context *context);

#endif /* _LIBC_TEST_LIBLEXICAL_TEST_H_ */

