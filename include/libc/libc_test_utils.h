
#ifndef _LIBC_LIBC_TEST_UTILS_H_
#define _LIBC_LIBC_TEST_UTILS_H_

enum string_func {
	FUNC_NONE = 0,
	FUNC_BZERO,
	FUNC_MEMSET,
	FUNC_MEMCMP,
	FUNC_MEMEQ,
	FUNC_MEMNCHR,
	FUNC_MEMCHR,
};

struct string_context {
	enum string_func function;
	unsigned char *expected_src;
	unsigned char *expected_dst;
	unsigned char *real_src;
	unsigned char *real_dst;
	size_t size;
	size_t offset;
	size_t needle;

	unsigned char chr;
};

void utest_print_compare(unsigned char *data, unsigned char *cmp, size_t size);
int utest_validate_memory(unsigned char *expected, unsigned char *real, size_t size);
void utest_generate_memory(unsigned char **m1, unsigned char **m2, size_t size, bool printable);
void utest_string_callback(struct string_context *context);
void utest_string_suite(size_t max_size, size_t max_offset, struct string_context *context, bool printable);

#endif /* _LIBC_LIBC_TEST_UTILS_H_ */

