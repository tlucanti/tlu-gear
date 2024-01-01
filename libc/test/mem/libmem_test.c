
#include <utest/utest.h>
#include <utest/utils.h>

#include <libc/test/libc_test_utils.h>
#include <libc/test/libmem_test.h>

UTEST(memzero)
{
	struct mem_context context;

	context.function = FUNC_MEMZERO;
	utest_mem_suite(64, 64, &context, true);
}

UTEST(memset)
{
	struct mem_context context;

	context.function = FUNC_MEMSET;
	utest_mem_suite(64, 64, &context, true);
}

UTEST(memcmp)
{
	struct mem_context context;

	context.function = FUNC_MEMCMP;
	utest_mem_suite(64, 64, &context, true);
}

UTEST(memeq)
{
	struct mem_context context;

	context.function = FUNC_MEMEQ;
	utest_mem_suite(64, 64, &context, true);
}

UTEST(memchr)
{
	struct mem_context context;

	context.function = FUNC_MEMCHR;
	utest_mem_suite(64, 64, &context, true);
}

UTEST(memnchr)
{
	struct mem_context context;

	context.function = FUNC_MEMNCHR;
	utest_mem_suite(64, 64, &context, true);
}

UTEST(memcpy)
{
	struct mem_context context;

	context.function = FUNC_MEMCPY;
	utest_mem_suite(64, 64, &context, true);
}

UTEST(memmove)
{
	struct mem_context context;

	context.function = FUNC_MEMMOVE;
	utest_mem_suite(64, 64, &context, true);
}

FUZZ(memzero)
{
	struct mem_context context;

	context.function = FUNC_MEMZERO;
	utest_mem_suite(512, 128, &context, false);
}

FUZZ(memset)
{
	struct mem_context context;

	context.function = FUNC_MEMSET;
	context.chr = 0xae;
	utest_mem_suite(512, 128, &context, false);
}

FUZZ(memcmp)
{
	struct mem_context context;

	context.function = FUNC_MEMCMP;
	utest_mem_suite(512, 128, &context, false);
}

FUZZ(memeq)
{
	struct mem_context context;

	context.function = FUNC_MEMEQ;
	utest_mem_suite(512, 128, &context, false);
}

FUZZ(memcpy)
{
	struct mem_context context;

	context.function = FUNC_MEMCPY;
	utest_mem_suite(512, 128, &context, false);
}

FUZZ(memmove)
{
	struct mem_context context;

	context.function = FUNC_MEMMOVE;
	utest_mem_suite(512, 128, &context, false);
}

int main(int argc, const char **argv)
{
	(void)argc;
	utest_random_init(1);
	unittest(argv);
}

