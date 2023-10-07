
#ifndef _UTEST_UTEST_H_
#define _UTEST_UTEST_H_

#include <core/compiler.h>
#include <utest/internal.h>
#include <stdbool.h>

#ifndef CONFIG_UTEST_CATCH_SEGFAULT
# define CONFIG_UTEST_CATCH_SEGFAULT true
#endif
#ifndef CONFIG_UTSET_COLOR_OUTPUT
# define CONFIG_UTEST_COLOR_OUTPUT true
#endif
#ifndef CONFIG_UTEST_FIRST_FAIL
# define CONFIG_UTEST_FIRST_FAIL false
#endif

void unittest(void);

#define UTEST(name) __UTEST_IMPL(name)
#define FUZZ(name) __FUZZ_IMPL(name) /* FIXME: make fuzzer test suite */

#include <stdlib.h>
#define ASSERT_FAIL(...) abort()

#endif /* _UTEST_UTEST_H_ */

