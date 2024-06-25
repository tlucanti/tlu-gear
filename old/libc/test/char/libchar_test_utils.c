
#include <libc/test/libc_test_utils.h>
#include <libc/test/libchar_test.h>
#include <utest/utest.h>
#include <utest/utils.h>
#include <core/panic.h>

#include <libc/char.h>

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

static void utest_ctype_callback(struct ctype_context *context)
{
	switch (context->function) {
	case FUNC_ISALNUM:
		context->name = "isalnum";
		context->real = tlu_isalnum(context->c);
		context->expected = !!isalnum(context->c);
		break;
	case FUNC_ISALPHA:
		context->name = "isalpha";
		context->real = tlu_isalpha(context->c);
		context->expected = !!isalpha(context->c);
		break;
	case FUNC_ISLOWER:
		context->name = "islower";
		context->real = tlu_islower(context->c);
		context->expected = !!islower(context->c);
		break;
	case FUNC_ISUPPER:
		context->name = "isupper";
		context->real = tlu_isupper(context->c);
		context->expected = !!isupper(context->c);
		break;
	case FUNC_ISPRINT:
		context->name = "isprint";
		context->real = tlu_isprint(context->c);
		context->expected = !!isprint(context->c);
		break;
	case FUNC_ISPUNCT:
		context->name = "ispunct";
		context->real = tlu_ispunct(context->c);
		context->expected = !!ispunct(context->c);
		break;
	case FUNC_ISSPACE:
		context->name = "isspace";
		context->real = tlu_isspace(context->c);
		context->expected = !!isspace(context->c);
		break;
	case FUNC_ISHEX:
		context->name = "ishex";
		context->real = tlu_ishex(context->c);
		context->expected = !!isxdigit(context->c);
		break;
	case FUNC_TOLOWER:
		context->name = "tolower";
		context->real = tlu_tolower(context->c);
		context->expected = (unsigned char)tolower(context->c);
		break;
	case FUNC_TOUPPER:
		context->name = "toupper";
		context->real = tlu_toupper(context->c);
		context->expected = (unsigned char)toupper(context->c);
		break;
	default:
		BUG("utest::ctype_suite: unknown function");
	}
}

void utest_ctype_suite(struct ctype_context *context)
{
	for (int c = 0; c <= UCHAR_MAX; ++c) {
		context->c = (unsigned char)c;
		utest_ctype_callback(context);

		if (context->real != context->expected) {
			printf("\nfunction %s char ", context->name);
			if (isprint(context->c)) {
				printf("%c (%d)", context->c, (int)context->c);
			} else {
				printf("(%d)\n", (int)context->c);
			}
		}
		ASSERT_EQUAL(context->expected, context->real);
	}
}

