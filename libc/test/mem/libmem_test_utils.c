
#include <libc/test/libc_test_utils.h>
#include <libc/test/libmem_test.h>
#include <utest/utest.h>
#include <utest/utils.h>
#include <core/panic.h>

#include <libc/mem.h>
#include <libc/string.h>

#include <string.h>
#include <stdio.h>

#ifndef rawmemchr
# define rawmemchr(s, c) memchr(s, c, -1)
#endif

static int utest_mem_callback(struct mem_context *context)
{
	intmax_t real_ret, expected_ret;
	const void *real_p, *expected_p;
	int ret;

	char *rsrc = (char *)context->real_src;
	char *rdst = (char *)context->real_dst;
	char *esrc = (char *)context->expected_src;
	char *edst = (char *)context->expected_dst;
	size_t size = context->size;
	size_t offset = context->offset;

	switch (context->function) {
	case FUNC_MEMZERO:
		tlu_memzero(rdst + offset, size);
		memset(edst + offset, 0, size);
		return NEXT_OFFSET;

	case FUNC_MEMSET:
		tlu_memset(rdst + offset, context->chr, size);
		memset(edst + offset, context->chr, size);
		return NEXT_OFFSET;

	case FUNC_MEMCPY:
		switch (context->state) {
		case 0:
			tlu_memcpy(rdst + offset, rsrc, size);
			memcpy(edst + offset, esrc, size);
			return NEXT_OFFSET_OR_STATE;
		case 1:
			tlu_memcpy(rdst, rsrc + offset, size);
			memcpy(edst, esrc + offset, size);
			return NEXT_OFFSET;
		default:
			BUG("utest::memcpy: invalid state");
		}
		break;

	case FUNC_MEMMOVE:
		switch (context->state) {
		case 0:
			tlu_memmove(rdst + offset, rsrc, size);
			memmove(edst + offset, esrc, size);
			return NEXT_OFFSET_OR_STATE;
		case 1:
			tlu_memmove(rdst, rsrc + offset, size);
			memmove(edst, esrc + offset, size);
			return NEXT_OFFSET_OR_STATE;
		case 2:
			tlu_memmove(rdst, rdst + offset, size);
			memmove(edst, edst + offset, size);
			return NEXT_OFFSET_OR_STATE;
		case 3:
			tlu_memmove(rdst + offset, rdst, size);
			memmove(edst + offset, edst, size);
			return NEXT_OFFSET;
		default:
			BUG("utest::memmove: invalid state");
		}
		BUG("utest:memmove: should not be there");

	case FUNC_MEMCMP:
		switch (context->state) {
		case 0:
			real_ret = tlu_memcmp(rsrc + offset, rdst, size);
			expected_ret = memcmp(esrc + offset, edst, size);
			ret = NEXT_OFFSET_OR_STATE;
			break;
		case 1:
			real_ret = tlu_memcmp(rsrc, rdst + offset, size);
			expected_ret = memcmp(esrc, edst + offset, size);
			ret = NEXT_OFFSET_OR_STATE;
			break;
		case 2:
			real_ret = tlu_memcmp(rsrc + offset, rsrc + offset, size);
			expected_ret = memcmp(esrc + offset, esrc + offset, size);
			ret = NEXT_OFFSET;
			break;
		default:
			BUG("utest::memcmp: invalid state");
		}

		ASSERT_EQUAL_SIGN(expected_ret, real_ret);
		return ret;

	case FUNC_MEMEQ:
		switch (context->state) {
		case 0:
			real_ret = tlu_memeq(rsrc + offset, rdst, size);
			expected_ret = memcmp(esrc + offset, edst, size);
			ret = NEXT_OFFSET_OR_STATE;
			break;
		case 1:
			real_ret = tlu_memeq(rsrc, rdst + offset, size);
			expected_ret = memcmp(esrc, edst + offset, size);
			ret = NEXT_OFFSET_OR_STATE;
			break;
		case 2:
			real_ret = tlu_memeq(rsrc + offset, rsrc + offset, size);
			expected_ret = memcmp(esrc + offset, esrc + offset, size);
			ret = NEXT_OFFSET;
			break;
		default:
			BUG("utest::memeq: invalid state");
		}

		expected_ret = (expected_ret == 0);
		ASSERT_EQUAL(expected_ret, real_ret);
		return ret;

	case FUNC_MEMNCHR:
		switch (context->state) {
		case 0:
			real_p = tlu_memnchr(rsrc + offset, rsrc[context->needle], size);
			expected_p = memchr(esrc + offset, esrc[context->needle], size);
			ret = NEXT_OFFSET_OR_STATE;
			break;
		case 1:
			real_p = tlu_memnchr(rsrc + offset, 0, size);
			expected_p = memchr(esrc + offset, 0, size);
			ret = NEXT_OFFSET;
			break;
		default:
			BUG("utest::memnchr: invalid state");
		}

		if (expected_p == NULL) {
			ASSERT_NULL(real_p);
		} else {
			expected_ret = (uintptr_t)expected_p - (uintptr_t)esrc;
			real_ret = (uintptr_t)real_p - (uintptr_t)rsrc;
			ASSERT_EQUAL(expected_ret, real_ret);
		}
		return ret;

	case FUNC_MEMCHR:
		BUG_ON(NULL == memchr(esrc + offset, esrc[context->needle], size + 1));

		real_p = tlu_memchr(rsrc + offset, rsrc[context->needle]);
		expected_p = rawmemchr(esrc + offset, esrc[context->needle]);

		if (expected_p == NULL) {
			ASSERT_NULL(real_p);
		} else {
			expected_ret = (uintptr_t)expected_p - (uintptr_t)esrc;
			real_ret = (uintptr_t)real_p - (uintptr_t)rsrc;
			ASSERT_EQUAL(expected_ret, real_ret);
		}
		return NEXT_OFFSET;

	default:
		BUG("utest::string_suite: unknown function");
	}
	BUG("utest:string_suite: should not be there");
}

int utest_mem_suite_run(size_t max_size, size_t max_offset,
			struct mem_context *context, bool printable,
			int (*callback)(struct mem_context *))
{
	unsigned char *expected_src, *expected_dst;
	unsigned char *real_src, *real_dst;
	size_t alloc_size;
	size_t offset;
	bool err = false;
	int ret;
	const size_t padding = 512;

	utest_progress_start();

	for (size_t size = 0; size <= max_size; ++size) {
		offset = 0;
next_offset:
		BUG_ON(offset > size);
		utest_progress(size, max_size + 1);

		alloc_size = padding + offset + size + padding;
		real_src = utest_malloc(alloc_size);
		real_dst = utest_malloc(alloc_size);
		expected_src = utest_malloc(alloc_size);
		expected_dst = utest_malloc(alloc_size);

		utest_generate_memory(real_src + padding + offset,
				      expected_src + padding + offset,
				      size, printable);
		utest_generate_memory(real_dst + padding + offset,
				      expected_dst + padding + offset,
				      size, printable);

		context->real_src = real_src + padding + offset;
		context->real_dst = real_dst + padding + offset;
		context->expected_src = expected_src + padding + offset;
		context->expected_dst = expected_dst + padding + offset;

		context->size = size;
		context->offset = offset;
		context->needle = utest_random_range(offset, size);
		if (printable) {
			context->chr = utest_random_range('a', 'z');
		} else {
			context->chr = utest_random();
		}

		ret = callback(context);

		if (utest_validate_memory(expected_src, real_src, alloc_size)) {
			printf("src valdation error (state %d) with ", context->state);
			printf("size=%lu, ", size);
			printf("offset=%lu (%lu)\n", offset, offset % 8);
			err = true;
		}
		if (utest_validate_memory(expected_dst, real_dst, alloc_size)) {
			printf("dst valdation error (state %d) with ", context->state);
			printf("size=%lu, ", size);
			printf("offset=%lu (%lu)\n", offset, offset % 8);
			err = true;
		}
		ASSERT_FALSE(err);

		free(expected_src);
		free(expected_dst);
		free(real_src);
		free(real_dst);

		switch (ret) {
		case NEXT_STATE:
			ret = NEXT_STATE;
			break;
		case NEXT_OFFSET_OR_STATE:
			ret = NEXT_STATE;
			fallthrough;
		case NEXT_OFFSET:
			offset += 1;
			if (offset <= size && offset <= max_offset) {
				goto next_offset;
			}
			break;
		default:
			BUG("utest::string_suite: invalid return state");
		}
	}

	utest_progress_done();
	return ret;
}

void utest_mem_suite(size_t max_size, size_t max_offset, struct mem_context *context, bool printable)
{
	int ret;

	context->state = 0;
	while (true) {
		ret = utest_mem_suite_run(max_size, max_offset, context,
					  printable, utest_mem_callback);

		if (ret != NEXT_STATE) {
			break;
		}
		utest_ok();
		context->state++;
	}
}

