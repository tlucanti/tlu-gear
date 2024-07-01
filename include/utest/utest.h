
#ifndef _UTEST_UTEST_H_
#define _UTEST_UTEST_H_

#include <core/compiler.h>
#include <utest/internal.h>

void unittest(const char **argv);

#define UTEST(name) __UTEST_IMPL(name, false)
#define UTEST_SKIP(name) __UTEST_IMPL(name, true)

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

#define ASSERT_EQUAL_STR(exp, real) __assert_str(exp, real, true)
#define ASSERT_NOT_EQUAL_STR(exp, real) __assert_str(exp, real, false)
#define ASSERT_EQUAL_MEM(exp, real, size) __assert_mem(exp, real, size, true)
#define ASSERT_NOT_EQUAL_MEM(exp, real, size) __assert_mem(exp, real, size, false)

#define ASSERT_EQUAL_SIGN(exp, real) __assert_sign(exp, real, true)
#define ASSERT_NOT_EQUAL_SIGN(exp, real) __assert_sign(exp, real, false)

#define utest_panic(format, ...) __utest_panic(format, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define PANIC_ON(expr)                                  \
	do {                                            \
		if (unlikely(expr)) {                   \
			utest_panic("PANIC_ON failed"); \
		}                                       \
	} while (false)

extern __cold __noret __printf(1, 5) void
__utest_panic(const char *format, const char *file, const char *func, uint line, ...);

#endif /* _UTEST_UTEST_H_ */

