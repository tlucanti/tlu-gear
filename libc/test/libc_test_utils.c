
#define  _GNU_SOURCE

#include <core/color.h>
#include <core/panic.h>
#include <core/math.h>

#include <libc/libc.h>
#include <libc/libc_test_utils.h>
#include <utest/utest.h>
#include <utest/utils.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

void utest_print_compare(unsigned char *data, unsigned char *cmp, size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		if (data[i] != cmp[i]) {
			printf(ANSI_BRED);
		}

		if (isalnum(data[i])) {
			printf("  %c", data[i]);
		} else {
			printf("\\%02hhx", data[i]);
		}
		printf(ANSI_RESET);
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

	return EFAULT;
}

void utest_generate_memory(unsigned char **m1, unsigned char **m2, size_t size, bool printable)
{
	const char *alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned char c;

	*m1 = malloc(size);
	*m2 = malloc(size);

	panic_on(*m1 == NULL || *m2 == NULL, "out of memory");

	for (size_t i = 0; i < size; ++i) {
		if (printable) {
			c = alphabet[utest_random_range(0, strlen(alphabet) - 1)];
			BUG_ON(!isalnum(c), "bad byte generated");
		} else {
			c = (unsigned char)utest_random();
		}

		(*m1)[i] = c;
		(*m2)[i] = c;
	}
}

void utest_mem_callback(struct mem_context *context)
{
	int real_ret, expected_ret;
	const void *real_p, *expected_p;

	switch (context->function) {
	case FUNC_BZERO:
		tlu_bzero(context->real_dst + context->offset, context->size);
		bzero(context->expected_dst + context->offset, context->size);
		break;

	case FUNC_MEMSET:
		tlu_memset(context->real_dst + context->offset, context->chr, context->size);
		memset(context->expected_dst + context->offset, context->chr, context->size);
		break;

	case FUNC_MEMCMP:
		real_ret = tlu_memcmp(context->real_src + context->offset,
				      context->real_dst + context->offset,
				      context->size);
		expected_ret = memcmp(context->expected_src + context->offset,
				      context->expected_dst + context->offset,
				      context->size);
		ASSERT_EQUAL_SIGN(expected_ret, real_ret);

		real_ret = tlu_memcmp(context->real_src + context->offset,
				      context->real_src + context->offset,
				      context->size);
		expected_ret = memcmp(context->expected_src + context->offset,
				      context->expected_src + context->offset,
				      context->size);
		ASSERT_EQUAL(expected_ret, real_ret);
		break;

	case FUNC_MEMEQ:
		real_ret = tlu_memeq(context->real_src + context->offset,
				     context->real_dst + context->offset,
				     context->size);
		expected_ret = memcmp(context->expected_src + context->offset,
				      context->expected_dst + context->offset,
				      context->size);
		expected_ret = expected_ret == 0;
		ASSERT_EQUAL_SIGN(expected_ret, real_ret);

		real_ret = tlu_memeq(context->real_src + context->offset,
				     context->real_src + context->offset,
				     context->size);
		expected_ret = memcmp(context->expected_src + context->offset,
				      context->expected_src + context->offset,
				      context->size);
		expected_ret = expected_ret == 0;
		ASSERT_EQUAL(expected_ret, real_ret);
		break;

	case FUNC_MEMNCHR:
		real_p = tlu_memnchr(context->real_src + context->offset,
				     context->real_src[context->needle],
				     context->size);
		expected_p = memchr(context->expected_src + context->offset,
				    context->expected_src[context->needle],
				    context->size);
		ASSERT_EQUAL_PTR(expected_p, real_p);

		real_p = tlu_memnchr(context->real_src + context->offset, 0,
				     context->size);
		expected_p = memchr(context->expected_src + context->offset, 0,
				    context->size);
		ASSERT_EQUAL_PTR(expected_p, real_p);
		break;

	case FUNC_MEMCHR:
		BUG_ON(NULL == memchr(context->expected_src + context->offset,
				      context->expected_src[context->needle],
				      context->size));

		real_p = tlu_memchr(context->real_src + context->offset,
				    context->real_src[context->needle]);
		expected_p = rawmemchr(context->expected_src + context->offset,
				       context->expected_src[context->needle]);
		ASSERT_EQUAL_PTR(expected_p, real_p);

		real_p = tlu_memchr(context->real_src + context->offset, 0);
		expected_p =
			rawmemchr(context->expected_src + context->offset, 0);
		ASSERT_EQUAL_PTR(expected_p, real_p);
		break;

	default:
		panic("unknown function");
	}
}

void utest_mem_suite(size_t max_size, size_t max_offset, struct mem_context *context, bool printable)
{
	unsigned char *expected_src, *expected_dst;
	unsigned char *real_src, *real_dst;
	size_t alloc_size;
	const size_t offset_start = 10;
	bool err = false;

	utest_progress_start();

	for (size_t size = 0; size <= max_size; ++size) {
		for (size_t offset = offset_start; offset < max_offset; ++offset) {
			utest_progress(size * (max_offset - offset_start) + offset - offset_start, (max_size + 1) * (max_offset - offset_start));

			alloc_size = offset_start + offset + size + offset_start;
			BUG_ON(offset + offset_start >= alloc_size, "offset is too big");
			utest_generate_memory(&expected_src, &real_src, alloc_size, printable);
			utest_generate_memory(&expected_dst, &real_dst, alloc_size, printable);

			context->real_src = real_src;
			context->real_dst = real_dst;
			context->expected_src = expected_src;
			context->expected_dst = expected_dst;
			context->real_dst = real_dst;

			context->size = size;
			context->offset = offset;
			context->needle = utest_random_range(context->offset, max(context->size, context->offset));

			utest_mem_callback(context);

			if (utest_validate_memory(expected_src, real_src, alloc_size)) {
				printf("src valdation error with ");
				printf("size=%lu, ", size);
				printf("offset=%lu\n", ((uintptr_t)real_src + offset) % 8);
				err = true;
			}
			if (utest_validate_memory(expected_dst, real_dst, alloc_size)) {
				printf("src valdation error with ");
				printf("size=%lu, ", size);
				printf("offset=%lu\n", ((uintptr_t)real_src + offset) % 8);
				err = true;
			}
			ASSERT_FALSE(err);

			free(expected_src);
			free(expected_dst);
			free(real_src);
			free(real_dst);
		}
	}

	utest_progress_done();
}

