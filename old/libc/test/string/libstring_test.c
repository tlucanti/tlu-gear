
#include <libc/test/libc_test_utils.h>
#include <libc/test/libstring_test.h>
#include <utest/utest.h>
#include <utest/utils.h>

#include <libc/string.h>

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

UTEST(sendswith)
{
	struct string_context context;

	context.function = FUNC_SENDSWITH;
	utest_string_suite(64, 64, &context, true);
}

UTEST(strstr)
{
	struct string_context context;
	const char *s;

	s = "111";
	ASSERT_EQUAL_PTR(s, tlu_strstr(s, "1"));
	ASSERT_EQUAL_PTR(s, tlu_strstr(s, "11"));
	ASSERT_EQUAL_PTR(NULL, tlu_strstr(s, "1111"));

	s = "aaba";
	ASSERT_EQUAL_PTR(s + 1, tlu_strstr(s, "aba"));

	context.function = FUNC_STRSTR;
	utest_string_suite(64, 64, &context, true);
}

UTEST(strrstr)
{
	struct string_context context;
	const char *s;

	s = "111";
	ASSERT_EQUAL_PTR(s + 2, tlu_strrstr(s, "1"));
	ASSERT_EQUAL_PTR(s + 1, tlu_strrstr(s, "11"));
	ASSERT_EQUAL_PTR(NULL, tlu_strrstr(s, "1111"));

	s = "aaba";
	ASSERT_EQUAL_PTR(s + 1, tlu_strrstr(s, "aba"));

	context.function = FUNC_STRRSTR;
	utest_string_suite(64, 64, &context, true);
}

UTEST(strcnt)
{
	struct string_context context;

	ASSERT_EQUAL(3, tlu_strcnt("aa", ""));
	ASSERT_EQUAL(1, tlu_strcnt("", ""));
	ASSERT_EQUAL(2, tlu_strcnt("SS", "S"));

	context.function = FUNC_STRCNT;
	utest_string_suite(64, 64, &context, true);
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

FUZZ(sendswith)
{
	struct string_context context;

	context.function = FUNC_SENDSWITH;
	utest_string_suite(512, 128, &context, false);
}

FUZZ(strstr)
{
	struct string_context context;

	context.function = FUNC_STRSTR;
	utest_string_suite(512, 128, &context, false);
}

FUZZ(strrstr)
{
	struct string_context context;

	context.function = FUNC_STRRSTR;
	utest_string_suite(512, 128, &context, false);
}

FUZZ(strcnt)
{
	struct string_context context;

	context.function = FUNC_STRCNT;
	utest_string_suite(512, 128, &context, false);
}

int main(int argc, const char **argv)
{
	(void)argc;
	utest_random_init(0);
	unittest(argv);
}

