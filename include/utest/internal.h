
#ifndef _UTEST_INTERNAL_H_
#define _UTEST_INTERNAL_H_

struct __utest {
	const char *name;
	void (*func)(void);
	unsigned long magic;
};

#define __UTEST_MAGIC 0xAB0BA
#define __UTEST_ATTR __used __aligned(1) __section(".utest")

#define __UTEST_IMPL(__name)                                           \
	void UTEST_##__name(void);                                     \
                                                                       \
	static struct __utest __UTEST_STRUCT_##__name __UTEST_ATTR = { \
		.name = #__name,                                       \
		.func = &UTEST_##__name,                               \
		.magic = 0xAB0BA                                       \
	};                                                             \
                                                                       \
	void UTEST_##__name(void)

#endif /* _UTEST_INTERNAL_H_ */

