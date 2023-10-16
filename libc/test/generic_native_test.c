
#include <core/color.h>
#include <core/panic.h>

#include <libc/libc.h>
#include <libc/libc_test_utils.h>
#include <utest/utest.h>
#include <utest/utils.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

UTEST(bzero)
{
	struct string_context context;

	context.function = FUNC_BZERO;
	utest_string_suite(64, 64, &context, true);
}

UTEST(memset)
{
	struct string_context context;

	context.function = FUNC_MEMSET;
	context.chr = 0xae;
	utest_string_suite(64, 64, &context, true);
}

UTEST(memcmp)
{
	struct string_context context;
	context.function = FUNC_MEMCMP;
	utest_string_suite(64, 64, &context, true);
}

UTEST(memceq)
{
	struct string_context context;
	context.function = FUNC_MEMEQ;
	utest_string_suite(64, 64, &context, true);
}

FUZZ(bzero)
{
	struct string_context context;

	context.function = FUNC_BZERO;
	utest_string_suite(500, 128, &context, false);
}

FUZZ(memset)
{
	struct string_context context;

	context.function = FUNC_MEMSET;
	context.chr = 0xae;
	utest_string_suite(500, 128, &context, false);
}

FUZZ(memcmp)
{
	struct string_context context;
	context.function = FUNC_MEMCMP;
	utest_string_suite(500, 128, &context, true);
}

FUZZ(memceq)
{
	struct string_context context;
	context.function = FUNC_MEMEQ;
	utest_string_suite(500, 128, &context, true);
}

int main()
{
	utest_random_init(0);
	unittest();
}

