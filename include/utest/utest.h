
#ifndef _UTEST_UTEST_H_
#define _UTEST_UTEST_H_

#include <core/compiler.h>
#include <utest/internal.h>

void unittest(void);

#define UTEST(name) __UTEST_IMPL(name)
#define FUZZ(name) __FUZZ_IMPL(name) /* FIXME: make fuzzer test suite */

#include <stdlib.h>
#define ASSERT_FAIL(...) abort()

#endif /* _UTEST_UTEST_H_ */

