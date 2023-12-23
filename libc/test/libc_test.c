
#include <libc/libc_test_utils.h>
#include <utest/utest.h>
#include <utest/utils.h>

UTEST(memzero)
{
	struct string_context context;

	context.function = FUNC_MEMZERO;
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

UTEST(memeq)
{
	struct string_context context;

	context.function = FUNC_MEMEQ;
	utest_string_suite(64, 64, &context, true);
}

UTEST(memchr)
{
	struct string_context context;

	context.function = FUNC_MEMCHR;
	utest_string_suite(64, 64, &context, true);
}

UTEST(memnchr)
{
	struct string_context context;

	context.function = FUNC_MEMNCHR;
	utest_string_suite(64, 64, &context, true);
}

UTEST(memcpy)
{
	struct string_context context;

	context.function = FUNC_MEMCPY;
	utest_string_suite(64, 64, &context, true);
}

UTEST(memmove)
{
	struct string_context context;

	context.function = FUNC_MEMMOVE;
	utest_string_suite(64, 64, &context, true);
}

UTEST(strlen)
{
	struct string_context context;

	context.function = FUNC_STRLEN;
	utest_string_suite(64, 64, &context, true);
}

UTEST(strcmp)
{
	struct string_context context;

	context.function = FUNC_STRCMP;
	utest_string_suite(64, 64, &context, true);
}

UTEST(streq)
{
	struct string_context context;

	context.function = FUNC_STREQ;
	utest_string_suite(64, 64, &context, true);
}

UTEST(strchr)
{
	struct string_context context;

	context.function = FUNC_STRCHR;
	utest_string_suite(64, 64, &context, true);
}

UTEST(strrchr)
{
	struct string_context context;

	context.function = FUNC_STRRCHR;
	utest_string_suite(64, 64, &context, true);
}

UTEST(sstartswith)
{
	struct string_context context;

	context.function = FUNC_SSTARTSWITH;
	utest_string_suite(64, 64, &context, true);
}

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

FUZZ(memzero)
{
	struct string_context context;

	context.function = FUNC_MEMZERO;
	utest_string_suite(512, 128, &context, false);
}

FUZZ(memset)
{
	struct string_context context;

	context.function = FUNC_MEMSET;
	context.chr = 0xae;
	utest_string_suite(512, 128, &context, false);
}

FUZZ(memcmp)
{
	struct string_context context;

	context.function = FUNC_MEMCMP;
	utest_string_suite(512, 128, &context, false);
}

FUZZ(memeq)
{
	struct string_context context;

	context.function = FUNC_MEMEQ;
	utest_string_suite(512, 128, &context, false);
}

FUZZ(memcpy)
{
	struct string_context context;

	context.function = FUNC_MEMCPY;
	utest_string_suite(512, 128, &context, false);
}

FUZZ(memmove)
{
	struct string_context context;

	context.function = FUNC_MEMMOVE;
	utest_string_suite(512, 128, &context, false);
}

FUZZ(strlen)
{
	struct string_context context;

	context.function = FUNC_STRLEN;
	utest_string_suite(512, 128, &context, false);
}

FUZZ(strcmp)
{
	struct string_context context;

	context.function = FUNC_STRCMP;
	utest_string_suite(512, 128, &context, false);
}

FUZZ(streq)
{
	struct string_context context;

	context.function = FUNC_STREQ;
	utest_string_suite(512, 128, &context, false);
}

FUZZ(strchr)
{
	struct string_context context;

	context.function = FUNC_STRCHR;
	utest_string_suite(512, 128, &context, false);
}

FUZZ(strrchr)
{
	struct string_context context;

	context.function = FUNC_STRRCHR;
	utest_string_suite(512, 128, &context, false);
}

FUZZ(sstartswith)
{
	struct string_context context;

	context.function = FUNC_SSTARTSWITH;
	utest_string_suite(512, 128, &context, false);
}

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
	utest_random_init(1);
	unittest(argv);
}
