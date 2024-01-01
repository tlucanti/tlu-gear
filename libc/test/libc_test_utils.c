
#include <core/panic.h>
#include <core/error.h>
#include <utest/utils.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void utest_print_compare(unsigned char *data, unsigned char *cmp, size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		if (data[i] == cmp[i]) {
			continue;
		}

		if (isalnum(data[i])) {
			utest_print_red("  %c", data[i]);
		} else {
			utest_print_red("\\%02hhx", data[i]);
		}
	}
}

int utest_validate_memory(unsigned char *expected, unsigned char *real, size_t size)
{
	if (memcmp(expected, real, size) == 0) {
		return 0;
	}

	printf("\nexpected: ");
	utest_print_compare(expected, real, size);
	printf("\nreal:     ");
	utest_print_compare(real, expected, size);
	printf("\n");

	return TLU_EFAULT;
}

void utest_generate_memory(unsigned char *m1, unsigned char *m2, size_t size, bool printable)
{
	const char *alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned char c;

	for (size_t i = 0; i < size; ++i) {
		if (printable) {
			c = alphabet[utest_random_range(0, strlen(alphabet) - 1)];
			BUG_ON(!isalnum(c), "bad byte generated");
		} else {
			c = (unsigned char)utest_random();
		}

		m1[i] = c;
		m2[i] = c;
	}
}

