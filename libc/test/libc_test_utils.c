
#include <core/panic.h>
#include <core/error.h>
#include <core/math.h>
#include <core/color.h>
#include <utest/utils.h>
#include <libc/test/libc_test_utils.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void utest_print_compare(const unsigned char *data, size_t data_size,
				const unsigned char *cmp, size_t cmp_size,
				bool invert)
{
	size_t max_size = max(data_size, cmp_size);
	size_t min_size = min(data_size, cmp_size);
	const char *color;

	if (invert) {
		color = ANSI_BRED;
	} else {
		color = ANSI_BGREEN;
	}

	for (size_t i = 0; i < max_size; ++i) {
		if (i < min_size && data[i] == cmp[i]) {
			continue;
		}

		if (i < data_size) {
			if (isalnum(data[i]) || ispunct(data[i])) {
				utest_print_color(color, "  %c", data[i]);
			} else {
				utest_print_color(color, "\\%02hhx", data[i]);
			}
		} else {
			utest_print_color(color, " \\0");
		}
	}

}

int utest_validate_memory_differ(const unsigned char *expected, size_t exp_size,
				 const unsigned char *real, size_t real_size)
{
	if (exp_size != real_size) {
		utest_print_red("size differ\n");
	} else if (memcmp(expected, real, exp_size) == 0) {
		return 0;
	}

	printf("\nexpected: ");
	utest_print_compare(expected, exp_size, real, real_size, false);
	printf("\nreal:     ");
	utest_print_compare(real, real_size, expected, exp_size, true);
	printf("\n");

	return TLU_EFAULT;
}

int utest_validate_memory(const unsigned char *expected, const unsigned char *real, size_t size)
{
	return utest_validate_memory_differ(expected, size, real, size);
}

void utest_generate_memory(unsigned char *m1, unsigned char *m2, size_t size, bool printable)
{
	const char *alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned char c;

	for (size_t i = 0; i < size; ++i) {
		if (printable) {
			c = (unsigned char)alphabet[utest_random_range(0, strlen(alphabet) - 1)];
			BUG_ON(!isalnum(c), "bad byte generated");
		} else {
			c = (unsigned char)utest_random();
		}

		m1[i] = c;
		m2[i] = c;
	}
}

void utest_pipe(int fd[2])
{
	int ret = pipe(fd);

	panic_on(ret == -1, "utest_pipe: pipe failed");
}

