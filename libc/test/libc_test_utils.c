
#define  _GNU_SOURCE

#include <core/color.h>
#include <core/panic.h>
#include <core/math.h>

#include <libc/mem.h>
#include <libc/string.h>
#include <libc/char.h>
#include <libc/lexical.h>

#include <libc/libc_test_utils.h>
#include <utest/utest.h>
#include <utest/utils.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

enum state_machine {
	NEXT_STATE = 1,
	NEXT_OFFSET,
	NEXT_OFFSET_OR_STATE,
	STATE_DONE,
};

static void *utest_malloc(size_t size)
{
	void *p;

	p = malloc(size);
	panic_on(p == NULL, "out of memory");
	memset(p, 0xff, size);
	return p;
}

static void utest_print_compare(unsigned char *data, unsigned char *cmp, size_t size)
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

static int utest_validate_memory(unsigned char *expected, unsigned char *real, size_t size)
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

static void utest_generate_memory(unsigned char *m1, unsigned char *m2, size_t size, bool printable)
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

static int utest_string_callback(struct string_context *context)
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

	case FUNC_STRLEN:
		esrc[context->needle] = 0;
		rsrc[context->needle] = 0;
		BUG_ON(NULL == memchr(esrc + offset, 0, size + 1));

		real_ret = tlu_strlen(rsrc + offset);
		expected_ret = strlen(esrc + offset);
		ASSERT_EQUAL(expected_ret, real_ret);
		return NEXT_OFFSET;

	case FUNC_STRCMP:
		esrc[context->needle] = 0;
		rsrc[context->needle] = 0;
		BUG_ON(NULL == memchr(esrc + offset, 0, size + 1));

		switch (context->state) {
		case 0:
			real_ret = tlu_strcmp(rsrc + offset, rdst);
			expected_ret = strcmp(esrc + offset, edst);
			ret = NEXT_OFFSET_OR_STATE;
			break;
		case 1:
			real_ret = tlu_strcmp(rsrc, rdst + offset);
			expected_ret = strcmp(esrc, edst + offset);
			ret = NEXT_OFFSET_OR_STATE;
			break;
		case 2:
			real_ret = tlu_strcmp(rsrc + offset, rsrc + offset);
			expected_ret = strcmp(esrc + offset, esrc + offset);
			ret = NEXT_OFFSET;
			break;
		default:
			BUG("utest::strcmp: invalid state");
		}

		ASSERT_EQUAL_SIGN(expected_ret, real_ret);
		return ret;

	case FUNC_STREQ:
		esrc[context->needle] = 0;
		rsrc[context->needle] = 0;
		BUG_ON(NULL == memchr(esrc + offset, 0, size + 1));

		switch (context->state) {
		case 0:
			real_ret = tlu_streq(rsrc + offset, rdst);
			expected_ret = strcmp(esrc + offset, edst);
			ret = NEXT_OFFSET_OR_STATE;
			break;
		case 1:
			real_ret = tlu_streq(rsrc, rdst + offset);
			expected_ret = strcmp(esrc, edst + offset);
			ret = NEXT_OFFSET_OR_STATE;
			break;
		case 2:
			real_ret = tlu_streq(rsrc + offset, rsrc + offset);
			expected_ret = strcmp(esrc + offset, esrc + offset);
			ret = NEXT_OFFSET;
			break;
		default:
			BUG("utest::strcmp: invalid state");
		}

		expected_ret = (expected_ret == 0);
		ASSERT_EQUAL(expected_ret, real_ret);
		return ret;

	case FUNC_STRCHR:
		esrc[context->needle] = 0;
		rsrc[context->needle] = 0;
		BUG_ON(NULL == memchr(esrc + offset, esrc[context->needle], size + 1));

		switch (context->state) {
		case 0:
			real_p = tlu_strchr(rsrc + offset, rsrc[context->needle]);
			expected_p = strchr(esrc + offset, esrc[context->needle]);
			ret = NEXT_OFFSET_OR_STATE;
			break;
		case 1:
			real_p = tlu_strchr(rsrc + offset, 0);
			expected_p = strchr(esrc + offset, 0);
			ret = NEXT_OFFSET;
			break;
		default:
			BUG("utest::strchr: invalid state");
		}

		if (expected_p == NULL) {
			ASSERT_NULL(real_p);
		} else {
			expected_ret = (uintptr_t)expected_p - (uintptr_t)esrc;
			real_ret = (uintptr_t)real_p - (uintptr_t)rsrc;
			ASSERT_EQUAL(expected_ret, real_ret);
		}
		return ret;

	case FUNC_STRRCHR:
		esrc[context->needle] = 0;
		rsrc[context->needle] = 0;
		BUG_ON(NULL == memchr(esrc + offset, esrc[context->needle], size + 1));

		switch (context->state) {
		case 0:
			real_p = tlu_strrchr(rsrc + offset, rsrc[context->needle]);
			expected_p = strrchr(esrc + offset, esrc[context->needle]);
			ret = NEXT_OFFSET_OR_STATE;
			break;
		case 1:
			real_p = tlu_strrchr(rsrc + offset, 0);
			expected_p = strrchr(esrc + offset, 0);
			ret = NEXT_OFFSET;
			break;
		default:
			BUG("utest::strrchr: invalid state");
		}

		if (expected_p == NULL) {
			ASSERT_NULL(real_p);
		} else {
			expected_ret = (uintptr_t)expected_p - (uintptr_t)esrc;
			real_ret = (uintptr_t)real_p - (uintptr_t)rsrc;
			ASSERT_EQUAL(expected_ret, real_ret);
		}
		return ret;

	case FUNC_SSTARTSWITH:

#define __sstartswith(str, pattern) (strncmp(str, pattern, strlen(pattern)) == 0)
		esrc[size] = '\0';
		rsrc[size] = '\0';
		BUG_ON(NULL == memchr(esrc + offset, 0, size + 1));

		real_ret = 0;
		expected_ret = 0;

		switch (context->state) {
		case 0:
			real_ret = tlu_sstartswith(rsrc + offset, esrc + offset);
			expected_ret = __sstartswith(rsrc + offset, esrc + offset);
			ret = NEXT_OFFSET_OR_STATE;
			break;
		case 1:
			esrc[context->needle] = '\0';
			real_ret = tlu_sstartswith(rsrc + offset, esrc + offset);
			expected_ret = __sstartswith(rsrc + offset, esrc + offset);
			rsrc[context->needle] = '\0';
			ret = NEXT_OFFSET_OR_STATE;
			break;
		case 2:
			rsrc[context->needle] = '\0';
			real_ret = tlu_sstartswith(rsrc + offset, esrc + offset);
			expected_ret = __sstartswith(rsrc + offset, esrc + offset);
			esrc[context->needle] = '\0';
			ret = NEXT_OFFSET_OR_STATE;
			break;
		case 3:
			context->expected_src[context->needle] += 1;
			real_ret = tlu_sstartswith(rsrc + offset, esrc + offset);
			expected_ret = __sstartswith(rsrc + offset, esrc + offset);
			context->real_src[context->needle] += 1;
			ret = NEXT_OFFSET_OR_STATE;
			break;

		case 4:
			context->real_src[context->needle] += 1;
			real_ret = tlu_sstartswith(rsrc + offset, esrc + offset);
			expected_ret = __sstartswith(rsrc + offset, esrc + offset);
			context->expected_src[context->needle] += 1;
			ret = NEXT_OFFSET;
			break;
		default:
			BUG("utest::strcmp: invalid state");
		}

		ASSERT_EQUAL(expected_ret, real_ret);
		return ret;

	default:
		BUG("utest::string_suite: unknown function");
	}
	BUG("utest:string_suite: should not be there");
}

static int utest_string_suite_run(size_t max_size, size_t max_offset, struct string_context *context, bool printable)
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

		ret = utest_string_callback(context);

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

void utest_string_suite(size_t max_size, size_t max_offset, struct string_context *context, bool printable)
{
	context->state = 0;
	while (true) {
		if (utest_string_suite_run(max_size, max_offset, context, printable) != NEXT_STATE) {
			break;
		}
		utest_ok();
		context->state++;
	}
}

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
		context->expected = tolower(context->c);
		break;
	case FUNC_TOUPPER:
		context->name = "toupper";
		context->real = tlu_toupper(context->c);
		context->expected = toupper(context->c);
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

	default:
		BUG("utest::lexical_suite: unknown function");
	}
	BUG("utest:lexical_suite: should not be there");
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

