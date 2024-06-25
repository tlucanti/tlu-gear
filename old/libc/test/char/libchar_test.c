
#include <libc/test/libc_test_utils.h>
#include <libc/test/libchar_test.h>
#include <utest/utest.h>
#include <utest/utils.h>

UTEST(isalnum)
{
	struct ctype_context context;

	context.function = FUNC_ISALNUM;
	utest_ctype_suite(&context);
}

UTEST(isalpha)
{
	struct ctype_context context;

	context.function = FUNC_ISALNUM;
	utest_ctype_suite(&context);
}

UTEST(islower)
{
	struct ctype_context context;

	context.function = FUNC_ISLOWER;
	utest_ctype_suite(&context);
}

UTEST(isupper)
{
	struct ctype_context context;

	context.function = FUNC_ISUPPER;
	utest_ctype_suite(&context);
}

UTEST(isprint)
{
	struct ctype_context context;

	context.function = FUNC_ISPRINT;
	utest_ctype_suite(&context);
}

UTEST(ispunct)
{
	struct ctype_context context;

	context.function = FUNC_ISPUNCT;
	utest_ctype_suite(&context);
}

UTEST(isspace)
{
	struct ctype_context context;

	context.function = FUNC_ISSPACE;
	utest_ctype_suite(&context);
}

UTEST(ishex)
{
	struct ctype_context context;

	context.function = FUNC_ISHEX;
	utest_ctype_suite(&context);
}

UTEST(tolower)
{
	struct ctype_context context;

	context.function = FUNC_TOLOWER;
	utest_ctype_suite(&context);
}

UTEST(toupper)
{
	struct ctype_context context;

	context.function = FUNC_TOUPPER;
	utest_ctype_suite(&context);
}

int main(int argc, const char **argv)
{
	(void)argc;
	utest_random_init(1);
	unittest(argv);
}

