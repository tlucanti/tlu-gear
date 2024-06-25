
#include <libc/test/libc_test_utils.h>
#include <libc/test/liblexical_test.h>
#include <utest/utest.h>
#include <utest/utils.h>

UTEST(numtos)
{
	struct lexical_context context;

	context.function = FUNC_NUMTOS;
	utest_lexical_suite(10000, &context);
}

UTEST(unumtos)
{
	struct lexical_context context;

	context.function = FUNC_UNUMTOS;
	utest_lexical_suite(10000, &context);
}

UTEST(numtos_base)
{
	struct lexical_context context;

	context.function = FUNC_NUMTOS_BASE;
	utest_lexical_suite(10000, &context);
}

UTEST(unumtos_base)
{
	struct lexical_context context;

	context.function = FUNC_UNUMTOS_BASE;
	utest_lexical_suite(10000, &context);
}

UTEST(numtos_base_upper)
{
	struct lexical_context context;

	context.function = FUNC_NUMTOS_BASE_UPPER;
	utest_lexical_suite(10000, &context);
}

UTEST(unumtos_base_upper)
{
	struct lexical_context context;

	context.function = FUNC_UNUMTOS_BASE_UPPER;
	utest_lexical_suite(10000, &context);
}

FUZZ(numtos)
{
	struct lexical_context context;

	context.function = FUNC_NUMTOS;
	utest_lexical_suite(1000000, &context);
}

FUZZ(unumtos)
{
	struct lexical_context context;

	context.function = FUNC_UNUMTOS;
	utest_lexical_suite(1000000, &context);
}

FUZZ(numtos_base)
{
	struct lexical_context context;

	context.function = FUNC_NUMTOS_BASE;
	utest_lexical_suite(1000000, &context);
}

FUZZ(unumtos_base)
{
	struct lexical_context context;

	context.function = FUNC_UNUMTOS_BASE;
	utest_lexical_suite(1000000, &context);
}

FUZZ(numtos_base_upper)
{
	struct lexical_context context;

	context.function = FUNC_NUMTOS_BASE_UPPER;
	utest_lexical_suite(1000000, &context);
}

FUZZ(unumtos_base_upper)
{
	struct lexical_context context;

	context.function = FUNC_UNUMTOS_BASE_UPPER;
	utest_lexical_suite(1000000, &context);
}

int main(int argc, const char **argv)
{
	(void)argc;
	utest_random_init(0);
	unittest(argv);
}

