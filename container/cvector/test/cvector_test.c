
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
}

int main(int argc, const char **argv)
{
	(void)argc;
	cvector_init();
	unittest(argv);
	cvector_fini();
	return 0;
}

