
#include <utest/utest.h>
#include <utest/utils.h>

#include <libc/test/libc_test_utils.h>
#include <libc/test/libio_test.h>

#include <limits.h>
#include <string.h>
#include <malloc.h>

const uint64_t cases[] = {
	  0,
	  1,		(uint64_t)-1,
	  CHAR_MAX,	(uint64_t)CHAR_MIN,
	  UCHAR_MAX,
	  SHRT_MAX,	(uint64_t)SHRT_MIN,
	  USHRT_MAX,
	  INT_MAX,	(uint64_t)INT_MIN,
	  UINT_MAX,
	  LONG_MAX,	(uint64_t)LONG_MIN,
	  ULONG_MAX,
	  INT64_MAX,	(uint64_t)INT64_MIN,
	  UINT64_MAX,
};

UTEST(print_ushort)
{
	struct io_context context;

	context.function = FUNC_PRINT_USHORT;
	for (size_t i = 0; i < ARRAY_SIZE(cases); ++i) {
		utest_io_case(cases[i], &context);
	}
}

UTEST(print_short)
{
	struct io_context context;

	context.function = FUNC_PRINT_SHORT;
	for (size_t i = 0; i < ARRAY_SIZE(cases); ++i) {
		utest_io_case(cases[i], &context);
	}
}


UTEST(print_uint)
{
	struct io_context context;

	context.function = FUNC_PRINT_UINT;
	for (size_t i = 0; i < ARRAY_SIZE(cases); ++i) {
		utest_io_case(cases[i], &context);
	}
}

UTEST(print_int)
{
	struct io_context context;

	context.function = FUNC_PRINT_INT;
	for (size_t i = 0; i < ARRAY_SIZE(cases); ++i) {
		utest_io_case(cases[i], &context);
	}
}

UTEST(print_ulong)
{
	struct io_context context;

	context.function = FUNC_PRINT_ULONG;
	for (size_t i = 0; i < ARRAY_SIZE(cases); ++i) {
		utest_io_case(cases[i], &context);
	}
}

UTEST(print_long)
{
	struct io_context context;

	context.function = FUNC_PRINT_LONG;
	for (size_t i = 0; i < ARRAY_SIZE(cases); ++i) {
		utest_io_case(cases[i], &context);
	}
}

UTEST(print_char)
{
	struct io_context context;

	context.function = FUNC_PRINT_CHAR;
	for (size_t i = 0; i < ARRAY_SIZE(cases); ++i) {
		utest_io_case(cases[i], &context);
	}
}

UTEST(print_str)
{
	struct io_context context;

	context.function = FUNC_PRINT_STR;
	utest_io_str("", &context);
	utest_io_str("123", &context);
	utest_io_str("\x01\x02\x03", &context);
	utest_io_str("aaaaaaaaaaaa", &context);
	utest_io_str("!@#$%^&*()_+", &context);
}

FUZZ(print_ushort)
{
	struct io_context context;

	context.function = FUNC_PRINT_USHORT;
	utest_io_suite(100000, &context);
}

FUZZ(print_short)
{
	struct io_context context;

	context.function = FUNC_PRINT_SHORT;
	utest_io_suite(100000, &context);
}

FUZZ(print_uint)
{
	struct io_context context;

	context.function = FUNC_PRINT_UINT;
	utest_io_suite(100000, &context);
}

FUZZ(print_int)
{
	struct io_context context;

	context.function = FUNC_PRINT_INT;
	utest_io_suite(100000, &context);
}

FUZZ(print_ulong)
{
	struct io_context context;

	context.function = FUNC_PRINT_ULONG;
	utest_io_suite(100000, &context);
}

FUZZ(print_long)
{
	struct io_context context;

	context.function = FUNC_PRINT_LONG;
	utest_io_suite(100000, &context);
}

FUZZ(print_char)
{
	struct io_context context;

	context.function = FUNC_PRINT_CHAR;
	utest_io_suite(100000, &context);
}

FUZZ(print_str)
{
	const int size = 10000;
	struct io_context context;
	char *gen;

	gen = utest_malloc(size + 1);
	context.function = FUNC_PRINT_STR;
	utest_progress_start();

	for (int i = 0; i < size; ++i) {
		utest_progress(i, size);

		memset(gen, 0, size + 1);
		memset(gen, 'x', i);

		utest_io_str(gen, &context);
	}

	utest_progress_done();
	free(gen);
}

int main(int argc, const char **argv)
{
	(void)argc;
	utest_random_init(1);
	unittest(argv);
}

