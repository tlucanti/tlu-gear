
//#include <libc/io_test_utils.h>
#include <utest/utest.h>
#include <utest/utils.h>
#include <libc/io.h>

#include <string.h>

UTEST(putnum)
{
	putnum(123);
	ASSERT_EQUAL(0, memcmp(tlu_stdout.buffer, "123", 3));
	print_flush();
}

int main(int argc, const char **argv)
{
	(void)argc;
	utest_random_init(1);
	unittest(argv);
}

