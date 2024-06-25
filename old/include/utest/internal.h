
#ifndef _UTEST_INTERNAL_H_
#define _UTEST_INTERNAL_H_

#include <core/compiler.h>

#include <stdbool.h>
#include <stdint.h>
#include <setjmp.h>

struct __utest {
	const char *name;
	void (*func)(void);
	unsigned long magic;
	int skip;
};

extern jmp_buf __fall_buf;

#define __UTEST_MAGIC 0xB00B5
#define __FUZZ_MAGIC 0xDEADD0L
#define __UTEST_ATTR __used __aligned(1) __section(".utest")
#define __FUZZ_ATTR __used __aligned(1) __section(".fuzz")

#define __FUNC_NAME(__suite, __name) __suite##_##__name
#define __STRUCT_NAME(__suite, __name) __suite##_STRUCT_##__name

#define __FUZZ_IMPL(__name, __skip) \
	__SUITE_IMPL(FUZZ, __name, __FUZZ_ATTR, __FUZZ_MAGIC, __skip)
#define __UTEST_IMPL(__name, __skip) \
	__SUITE_IMPL(UTEST, __name, __UTEST_ATTR, __UTEST_MAGIC, __skip)

#define __SUITE_IMPL(__suite, __name, __attr, __magic, __skip)          \
	void __FUNC_NAME(__suite, __name)(void);                        \
                                                                        \
	static struct __utest __STRUCT_NAME(__suite, __name) __attr = { \
		.name = #__name,                                        \
		.func = &__FUNC_NAME(__suite, __name),                  \
		.magic = __magic,                                       \
		.skip = __skip                                          \
	};                                                              \
                                                                        \
	void __FUNC_NAME(__suite, __name)(void)

#define __assert_fail() __assert_fail_impl(__FILE__, __LINE__)
#define __assert_bool(exp, real) __assert_bool_impl(exp, real, __FILE__, __LINE__)
#define __assert_equal(exp, real, eq) __assert_eq_impl(exp, real, eq, __FILE__, __LINE__)
#define __assert_ptr(exp, real, eq) __assert_ptr_impl(exp, real, eq, __FILE__, __LINE__)
#define __assert_str(exp, real, eq) __assert_str_impl(exp, real, eq, __FILE__, __LINE__)
#define __assert_sign(exp, real, eq) __assert_sign_impl(exp, real, eq, __FILE__, __LINE__)
#define __assert_panic(exp, fall)                                           \
	do {                                                                \
		int __first_time, __was_panic;                              \
                                                                            \
		__assert_panic_prepare();                                   \
		__first_time = 1;                                           \
		__was_panic = setjmp(__fall_buf);                           \
                                                                            \
		if (__first_time) {                                         \
			__first_time = 0;                                   \
			(exp);                                              \
		}                                                           \
                                                                            \
		__assert_panic_fini(__was_panic, fall, __FILE__, __LINE__); \
	} while (false)

__cold __noret void __assert_fail_impl(const char *file, unsigned long line);
void __assert_bool_impl(bool exp, bool real, const char *file, unsigned long line);
void __assert_eq_impl(intmax_t exp, intmax_t real, bool eq, const char *file, unsigned long line);
void __assert_ptr_impl(const void *exp, const void *real, bool eq, const char *file, unsigned long line);
void __assert_str_impl(const char *exp, const char *real, bool eq, const char *file, unsigned long line);
void __assert_sign_impl(intmax_t exp, intmax_t real, bool eq, const char *file, unsigned long line);
void __assert_panic_prepare(void);
void __assert_panic_fini(int was_panic, int fall, const char *file, unsigned long line);

#endif /* _UTEST_INTERNAL_H_ */

