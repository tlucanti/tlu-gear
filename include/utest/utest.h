
#ifndef _UTEST_UTEST_H_
#define _UTEST_UTEST_H_

#include <core/compiler.h>
#include <utest/internal.h>

#define CONFIG_UTEST_FIRST_FAIL false
#define CONFIG_UTEST_CATCH_SEGFAULT false

#ifndef CONFIG_UTEST_CATCH_SEGFAULT
# define CONFIG_UTEST_CATCH_SEGFAULT true
#endif
#ifndef CONFIG_UTSET_COLOR_OUTPUT
# define CONFIG_UTEST_COLOR_OUTPUT true
#endif
#ifndef CONFIG_UTEST_FIRST_FAIL
# define CONFIG_UTEST_FIRST_FAIL false
#endif

void unittest(const char **argv);

#define UTEST(name) __UTEST_IMPL(name, false)
#define UTEST_SKIP(name) __UTEST_IMPL(name, true)
#define FUZZ(name) __FUZZ_IMPL(name, false)
#define FUZZ_SKIP(name) __FUZZ_IMPL(name, true)

#define ASSERT_FAIL() __assert_fail()
#define ASSERT_FALSE(expr) __assert_bool(false, expr)
#define ASSERT_TRUE(expr) __assert_bool(true, expr)

#define ASSERT_ZERO(expr) __assert_equal(0, expr, true)
#define ASSERT_NOT_ZERO(expr) __assert_equal(0, expr, false)
#define ASSERT_EQUAL(exp, real) __assert_equal(exp, real, true)
#define ASSERT_NOT_EQUAL(exp, real) __assert_equal(exp, real, false)

#define ASSERT_NULL(expr) __assert_ptr(NULL, expr, true)
#define ASSERT_NOT_NULL(expr) __assert_ptr(NULL, expr, false)
#define ASSERT_EQUAL_PTR(exp, real) __assert_ptr(exp, real, true)
#define ASSERT_NOT_EQUAL_PTR(exp, real) __assert_ptr(exp, real, false)

#define ASSERT_EQUAL_SIGN(exp, real) __assert_sign(exp, real, true)
#define ASSERT_NOT_EQUAL_SIGN(exp, real) __assert_sign(exp, real, false)

#endif /* _UTEST_UTEST_H_ */

