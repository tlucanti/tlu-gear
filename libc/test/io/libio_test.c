
#include <utest/utest.h>
#include <utest/utils.h>

#include <libc/test/libc_test_utils.h>
#include <libc/test/libio_test.h>

#include <limits.h>

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

UTEST(putnum_to_edge)
{
	struct io_context context;

	context.function = FUNC_PUTNUM_TO;
	for (size_t i = 0; i < ARRAY_SIZE(cases); ++i) {
		utest_io_case(cases[i], &context);
	}
}

UTEST(putunum_to_edge)
{
	struct io_context context;

	context.function = FUNC_PUTUNUM_TO;
	for (size_t i = 0; i < ARRAY_SIZE(cases); ++i) {
		utest_io_case(cases[i], &context);
	}
}

UTEST(putnum_to)
{
	struct io_context context;

	context.function = FUNC_PUTNUM_TO;
	utest_io_suite(1000, &context);
}

UTEST(putunum_to)
{
	struct io_context context;

	context.function = FUNC_PUTUNUM_TO;
	utest_io_suite(1000, &context);
}

FUZZ(putnum_to)
{
	struct io_context context;

	context.function = FUNC_PUTNUM_TO;
	utest_io_suite(100000, &context);
}

FUZZ(putunum_to)
{
	struct io_context context;

	context.function = FUNC_PUTUNUM_TO;
	utest_io_suite(100000, &context);
}

int main(int argc, const char **argv)
{
	(void)argc;
	utest_random_init(1);
	unittest(argv);
}

