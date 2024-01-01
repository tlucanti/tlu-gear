
#include <core/panic.h>
#include <core/error.h>
#include <utest/utest.h>
#include <utest/utils.h>

#include <libc/lexical.h>
#include <libc/test/liblexical_test.h>
#include <libc/test/libc_test_utils.h>

#include <stdio.h>
#include <limits.h>

static int utest_lexical_callback(struct lexical_context *context)
{
	switch (context->function) {
	case FUNC_NUMTOS:
		numtos(context->real, context->number);
		sprintf(context->expected, "%jd", context->number);
		return STATE_DONE;

	case FUNC_UNUMTOS:
		unumtos(context->real, context->unumber);
		sprintf(context->expected, "%ju", context->unumber);
		return STATE_DONE;

	case FUNC_NUMTOS_BASE:
		switch (context->state) {
		case 0:
			numtos_base(context->real, context->number, 10);
			sprintf(context->expected, "%jd", context->number);
			return NEXT_STATE;
		case 1:
			if (context->number >= 0) {
				numtos_base(context->real, context->number, 8);
				sprintf(context->expected, "%jo", context->number);
			}
			return NEXT_STATE;
		case 2:
			if (context->number >= 0) {
				numtos_base(context->real, context->number, 16);
				sprintf(context->expected, "%jx", context->number);
			}
			return STATE_DONE;
		default:
			BUG("utest::numtos_base: invalid state");
		}
		BUG("utest::numtos_base: should not be here");

	case FUNC_UNUMTOS_BASE:
		switch (context->state) {
		case 0:
			numtos_base(context->real, context->number, 10);
			sprintf(context->expected, "%jd", context->number);
			return NEXT_STATE;
		case 1:
			unumtos_base(context->real, context->number, 8);
			sprintf(context->expected, "%jo", context->number);
			return NEXT_STATE;
		case 2:
			unumtos_base(context->real, context->number, 16);
			sprintf(context->expected, "%jx", context->number);
			return STATE_DONE;
		default:
			BUG("utest::unumtos_base: invalid state");
		}
		BUG("utest::unumtos_base: should not be here");

	case FUNC_NUMTOS_BASE_UPPER:
		if (context->number >= 0) {
			numtos_base_upper(context->real, context->number, 16);
			sprintf(context->expected, "%jX", context->number);
		}
		return STATE_DONE;

	case FUNC_UNUMTOS_BASE_UPPER:
		if (context->number >= 0) {
			unumtos_base_upper(context->real, context->number, 16);
			sprintf(context->expected, "%jX", context->number);
		}
		return STATE_DONE;

	default:
		BUG("utest::lexical_suite: unknown function");
	}
	BUG("utest::lexical_suite: should not be there");
}

static int utest_lexical_suite_run(long max_iter, struct lexical_context *context)
{
	const uintmax_t edge_values[] = {
		  0,
		  1,		-1,
		  CHAR_MAX,	CHAR_MIN,
		  SHRT_MAX,	SHRT_MIN,
		  INT_MAX,	INT_MIN,
		  LONG_MAX,	LONG_MIN,
		  INTMAX_MAX,	INTMAX_MIN
	};
	const size_t padding = 16;
	const size_t number_size = 100;
	const size_t lexical_test_size = padding + number_size + padding;

	char *real;
	char *expected;
	int ret, err;

	utest_progress_start();

	max_iter += ARRAY_SIZE(edge_values);
	for (long i = 0; i < max_iter; ++i) {
		utest_progress(i, max_iter);

		real = utest_malloc(lexical_test_size);
		expected = utest_malloc(lexical_test_size);

		context->real = real + padding;
		context->expected = expected + padding;

		if (i < (long)ARRAY_SIZE(edge_values)) {
			context->unumber = edge_values[i];
			context->number = edge_values[i];
		} else if (i < max_iter * 4 / 10) {
			context->unumber = utest_random_range(0, 100);
			context->number = utest_random_range(0, 200) - 100;
		} else if (i < max_iter * 7 / 10) {
			context->unumber = utest_random_range(0, 10000);
			context->number = utest_random_range(0, 20000) - 10000;
		} else {
			context->unumber = utest_random();
			context->number = context->unumber;
		}

		ret = utest_lexical_callback(context);
		err = utest_validate_memory((unsigned char *)expected,
					    (unsigned char *)real,
					    lexical_test_size);
		ASSERT_FALSE(err);

		free(expected);
		free(real);
	}

	utest_progress_done();
	return ret;
}

void utest_lexical_suite(long max_iter, struct lexical_context *context)
{
	context->state = 0;
	while (true) {
		if (utest_lexical_suite_run(max_iter, context) != NEXT_STATE) {
			break;
		}
		utest_ok();
		context->state++;
	}
}

