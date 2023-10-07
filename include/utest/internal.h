
#ifndef _UTEST_INTERNAL_H_
#define _UTEST_INTERNAL_H_

struct __utest {
	const char *name;
	void (*func)(void);
	unsigned long magic;
	int skip;
};

#define __UTEST_MAGIC 0xB00B5
#define __FUZZ_MAGIC 0xDEADD0LL
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

#endif /* _UTEST_INTERNAL_H_ */

