
#include <core/types.h>
#include <utest/utest.h>

#include <libc/char.h>

#include <ctype.h>

UTEST(isalnum)
{
	for (uint c = 0; c < UINT8_MAX; c++) {
		ASSERT_EQUAL_BOOL(isalnum(c), tlu_isalnum(c));
	}
}

UTEST(isalpha)
{
	for (uint c = 0; c < UINT8_MAX; c++) {
		ASSERT_EQUAL_BOOL(isalpha(c), tlu_isalpha(c));
	}
}

UTEST(isdigit)
{
	for (uint c = 0; c < UINT8_MAX; c++) {
		ASSERT_EQUAL_BOOL(isdigit(c), tlu_isdigit(c));
	}
}

UTEST(ishex)
{
	for (uint c = 0; c < UINT8_MAX; c++) {
		ASSERT_EQUAL_BOOL(isxdigit(c), tlu_ishex(c));
	}
}

UTEST(islower)
{
	for (uint c = 0; c < UINT8_MAX; c++) {
		ASSERT_EQUAL_BOOL(islower(c), tlu_islower(c));
	}
}

UTEST(isprint)
{
	for (uint c = 0; c < UINT8_MAX; c++) {
		ASSERT_EQUAL_BOOL(isprint(c), tlu_isprint(c));
	}
}

UTEST(ispunct)
{
	for (uint c = 0; c < UINT8_MAX; c++) {
		ASSERT_EQUAL_BOOL(ispunct(c), tlu_ispunct(c));
	}
}

UTEST(isspace)
{
	for (uint c = 0; c < UINT8_MAX; c++) {
		ASSERT_EQUAL_BOOL(isspace(c), tlu_isspace(c));
	}
}

UTEST(isupper)
{
	for (uint c = 0; c < UINT8_MAX; c++) {
		ASSERT_EQUAL_BOOL(isupper(c), tlu_isupper(c));
	}
}

UTEST(tolower)
{
	for (uint c = 0; c < UINT8_MAX; c++) {
		ASSERT_EQUAL(tolower(c), tlu_tolower(c));
	}
}

UTEST(toupper)
{
	for (uint c = 0; c < UINT8_MAX; c++) {
		ASSERT_EQUAL(toupper(c), tlu_toupper(c));
	}
}

int main(int argc, const char **argv)
{
	(void)argc;
	unittest(argv);
	return 0;
}

