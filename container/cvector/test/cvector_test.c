
#include <container/cvector.h>
#include <utest/utest.h>

#include "../cvector_internal.h"
#include <string.h>
#include <setjmp.h>

#if CONFIG_CVECTOR_VALIDATION_LAYER
static jmp_buf jump_buf;
#define ASSERT_PANIC(expr)                        \
	do {                                      \
		__cvector_expected_panic = true;  \
		if (setjmp(jump_buf) == 0) {      \
			(void)(expr);             \
		}                                 \
		__cvector_expected_panic = false; \
	} while (false)
#else
# define ASSERT_PANIC(expr) /* nothing */
#endif

#define touch_memory(x)                   \
	do {                              \
		memset(&x, 0, sizeof(x)); \
	} while (false)

static bool __cvector_expected_panic = false;

void cvector_panic(const char *message)
{
	if (__cvector_expected_panic) {
		longjmp(jump_buf, 1);
	} else {
		ASSERT_FAIL(message);
	}
}

UTEST(cvector_create)
{
	const uint n = 31;
	int8 *v = cvector_create(int8, n, 0);
	struct cvector *cv = cvector_entry(v);

	ASSERT_EQUAL_PTR(v, cv->data);
	ASSERT_EQUAL(n, cv->size);
	ASSERT_GREATER_EQUAL(n, cv->allocated);
	check_magic(cv);

	for (uint i = 0; i < n; i++) {
		touch_memory(v[i]);
	}

	cvector_destroy(v);
}

UTEST(cvector_create2)
{
	const uint n = 10;
	uint64 *v = cvector_create(uint64, n, 0);
	struct cvector *cv = cvector_entry(v);

	ASSERT_EQUAL_PTR(v, cv->data);
	ASSERT_EQUAL(n, cv->size);
	ASSERT_GREATER_EQUAL(n, cv->allocated);
	check_magic(cv);

	for (uint i = 0; i < n; i++) {
		touch_memory(v[i]);
	}

	cvector_destroy(v);
}

UTEST(cvector_create_ext)
{
	const uint n = 10;
	char **v = cvector_create(char *, n, CVECTOR_CREATE_ZERO);
	struct cvector *cv = cvector_entry(v);

	ASSERT_EQUAL_PTR(v, cv->data);
	ASSERT_EQUAL(n, cv->size);
	ASSERT_GREATER_EQUAL(n, cv->allocated);
	check_magic(cv);

	for (uint i = 0; i < n; i++) {
		ASSERT_NULL(v[i]);
	}

	cvector_destroy(v);
}

struct test_struct {
	uint64 q;
	double w;
	char *e;
};

UTEST(cvector_create_ext2)
{
	const uint n = 7;
	struct test_struct *v = cvector_create(struct test_struct, n, CVECTOR_CREATE_EXACT_SIZE);
	struct cvector *cv = cvector_entry(v);

	ASSERT_EQUAL_PTR(v, cv->data);
	ASSERT_EQUAL(n, cv->size);
	ASSERT_EQUAL(n, cv->allocated);
	check_magic(cv);

	for (uint i = 0; i < n; i++) {
		touch_memory(v[i]);
	}

	cvector_destroy(v);
}

UTEST(cvector_create_ext3)
{
	const uint n = 10;
	double *v = cvector_create(double, n, CVECTOR_CREATE_ONLY_PREALLOC);
	struct cvector *cv = cvector_entry(v);

	ASSERT_EQUAL(0, cv->size);
	ASSERT_GREATER_EQUAL(n, cv->allocated);

	for (uint i = 0; i < n; i++) {
		touch_memory(v[i]);
	}

	cvector_destroy(v);
}

UTEST(cvector_create_ext4)
{
	int16 *v = cvector_create(int16, 0, CVECTOR_CREATE_ONLY_PREALLOC | CVECTOR_CREATE_EXACT_SIZE);
	struct cvector *cv = cvector_entry(v);

	ASSERT_EQUAL(0, cv->size);
	ASSERT_EQUAL(0, cv->allocated);

	cvector_destroy(v);
}

UTEST(cvector_copy)
{
	uint16 *v = cvector_create(uint16, 5, 0);
	uint16 *c;

	struct cvector *cv;
	struct cvector *cc;

	for (uint i = 0; i < 5; i++) {
		v[i] = i;
	}

	c = cvector_copy(v, 0);
	cv = cvector_entry(v);
	cc = cvector_entry(c);

	ASSERT_EQUAL(cv->size, cc->size);
	ASSERT_EQUAL(cv->allocated, cc->allocated);
	ASSERT_ZERO(memcmp(c, v, cv->size * sizeof(uint16)));

	cvector_destroy(v);
	cvector_destroy(c);
}

UTEST(cvector_copy_ext)
{
	int32 *v = cvector_create(int32, 13, 0);
	struct cvector *cv = cvector_entry(v);

	for (uint i = 0; i < 13; i++) {
		v[i] = i * 10 + i;
	}

	{
		int32 *c1 = cvector_copy(v, CVECTOR_COPY_EMPTY);
		struct cvector *cc1 = cvector_entry(c1);

		ASSERT_EQUAL(0, cc1->size);
		ASSERT_EQUAL(cv->allocated, cc1->allocated);

		cvector_destroy(c1);
	}
	{
		int32 *c2 = cvector_copy(v, CVECTOR_COPY_EXACT_SIZE);
		struct cvector *cc2 = cvector_entry(c2);

		ASSERT_EQUAL(cv->size, cc2->size);
		ASSERT_EQUAL(cv->size, cc2->allocated);
		ASSERT_ZERO(memcmp(c2, v, cv->size * sizeof(int32)));

		cvector_destroy(c2);
	}
	{
		int32 *c3 = cvector_copy(v, CVECTOR_COPY_EXACT_SIZE | CVECTOR_COPY_EMPTY);
		struct cvector *cc3 = cvector_entry(c3);

		ASSERT_EQUAL(0, cc3->size);
		ASSERT_EQUAL(cv->size, cc3->allocated);

		cvector_destroy(c3);
	}
	cvector_destroy(v);
}

UTEST(cvector_create_from)
{
	int64 init[] = {1, 2, 3, 4, 5};
	const uint n = ARRAY_SIZE(init);
	int64 *v = cvector_create_from(init, init + n, 0);
	struct cvector *cv = cvector_entry(v);

	ASSERT_EQUAL(n, cv->size);
	ASSERT_GREATER_EQUAL(n, cv->allocated);
	ASSERT_ZERO(memcmp(init, v, sizeof(int64) * n));

	cvector_destroy(v);
}

UTEST(cvector_create_from2)
{
	const void *begin = (const void *)200ul;
	const void *end = (const void *)100ul;

	ASSERT_PANIC(cvector_create_from(begin, end, 0));
}

UTEST(cvector_create_from_ext)
{
	const uint n = 9;
	int8 *c = cvector_create(int8, n, 0);
	int8 *v;
	struct cvector *cv;

	for (uint i = 0; i < n; i++) {
		c[i] = i * 10 + i;
	}
	v = cvector_create_from(c, c + n, CVECTOR_CREATE_FROM_EXACT_SIZE);
	cv = cvector_entry(v);

	ASSERT_EQUAL(n, cv->size);
	ASSERT_EQUAL(n, cv->allocated);
	ASSERT_ZERO(memcmp(c, v, sizeof(int8) * n));

	cvector_destroy(c);
	cvector_destroy(v);
}

UTEST(cvector_size)
{
	unsigned char *v1 = cvector_create(unsigned char, 0, 0);
	unsigned char *v2 = cvector_create(unsigned char, 4, 0);
	unsigned char *v3 = cvector_create(unsigned char, 10, CVECTOR_CREATE_ONLY_PREALLOC);

	ASSERT_EQUAL(0, cvector_size(v1));
	ASSERT_EQUAL(4, cvector_size(v2));
	ASSERT_EQUAL(0, cvector_size(v3));

	cvector_destroy(v1);
	cvector_destroy(v2);
	cvector_destroy(v3);
}

UTEST(cvector_empty)
{
	char *v1 = cvector_create(char, 0, 0);
	char *v2 = cvector_create(char, 4, 0);
	char *v3 = cvector_create(char, 10, CVECTOR_CREATE_ONLY_PREALLOC);

	ASSERT_TRUE(cvector_empty(v1));
	ASSERT_FALSE(cvector_empty(v2));
	ASSERT_TRUE(cvector_empty(v3));

	cvector_destroy(v1);
	cvector_destroy(v2);
	cvector_destroy(v3);
}


UTEST(cvector_capacity)
{
	unsigned char *v1 = cvector_create(unsigned char, 0, 0);
	unsigned char *v2 = cvector_create(unsigned char, 4, 0);
	unsigned char *v3 = cvector_create(unsigned char, 10, CVECTOR_CREATE_EXACT_SIZE);

	ASSERT_GREATER_EQUAL(0, cvector_capacity(v1));
	ASSERT_GREATER_EQUAL(4, cvector_capacity(v2));
	ASSERT_EQUAL(10, cvector_capacity(v3));

	cvector_destroy(v1);
	cvector_destroy(v2);
	cvector_destroy(v3);
}

UTEST(cvector_at)
{
	int *v = cvector_create(int, 3, 0);

	v[0] = 1;
	v[1] = 2;
	v[2] = 3;

	ASSERT_EQUAL(1, cvector_at(v, 0));
	ASSERT_EQUAL(2, cvector_at(v, 1));
	ASSERT_EQUAL(3, cvector_at(v, 2));

	ASSERT_PANIC(cvector_at(v, 3));
	ASSERT_PANIC(cvector_at(v, -1));

	cvector_at(v, 1) = 123;
	ASSERT_EQUAL(123, cvector_at(v, 1));

	cvector_destroy(v);
}

UTEST(cvector_rat)
{
	int *v = cvector_create(int, 3, 0);

	v[0] = 1;
	v[1] = 2;
	v[2] = 3;

	ASSERT_EQUAL(3, cvector_rat(v, 0));
	ASSERT_EQUAL(2, cvector_rat(v, 1));
	ASSERT_EQUAL(1, cvector_rat(v, 2));

	ASSERT_PANIC(cvector_rat(v, 3));
	ASSERT_PANIC(cvector_rat(v, -1));

	cvector_rat(v, 1) = 123;
	ASSERT_EQUAL(123, cvector_rat(v, 1));

	cvector_destroy(v);
}

UTEST(cvector_front)
{
	int *v1 = cvector_create(int, 0, 0);
	int *v2 = cvector_create(int, 3, 0);

	v2[0] = 1;
	v2[1] = 2;
	v2[3] = 3;

	ASSERT_EQUAL(1, cvector_front(v2));
	ASSERT_PANIC(cvector_front(v1));

	cvector_front(v2) = 321;
	ASSERT_EQUAL(321, cvector_front(v2));

	cvector_destroy(v1);
	cvector_destroy(v2);
}

UTEST(cvector_back)
{
	int *v1 = cvector_create(int, 0, 0);
	int *v2 = cvector_create(int, 3, 0);

	v2[0] = 1;
	v2[1] = 2;
	v2[2] = 3;

	ASSERT_EQUAL(3, cvector_back(v2));
	ASSERT_PANIC(cvector_front(v1));

	cvector_back(v2) = 321;
	ASSERT_EQUAL(321, cvector_back(v2));

	cvector_destroy(v1);
	cvector_destroy(v2);
}

int main(int argc, const char **argv)
{
	(void)argc;
	cvector_init();
	unittest(argv);
	cvector_fini();
	return 0;
}

