
#include <core/common.h>

struct __utest {
	const char *name;
	void (*func)(void);
	unsigned long magic;
};

#define __UTEST_MAGIC 0xAB0BA
#define __UTEST_ATTR __used __aligned(1) __section(".utest")

#define UTEST(name)                                                  \
	void UTEST_##name(void);                                     \
                                                                     \
	static struct __utest __UTEST_STRUCT_##name __UTEST_ATTR = { \
		.name = #name,                                       \
		.func = &TLU_TEST_##name,                            \
		.magic = 0xAB0BA                                     \
	};                                                           \
                                                                     \
	void UTEST_##name(void)

