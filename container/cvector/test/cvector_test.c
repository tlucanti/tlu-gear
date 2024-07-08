
#include <container/cvector.h>
#include <utest/utest.h>

#include "../cvector_internal.h"
#include <string.h>

#define touch_memory(x)                   \
	do {                              \
		memset(&x, 0, sizeof(x)); \
	} while (false)

UTEST(cvector_create)
{
	const uint n = 31;
	int8 *v = cvector_create(int8, n);
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
	uint64 *v = cvector_create(uint64, n);
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
	float *v =
		cvector_create_ext(float, n, CVECTOR_CREATE_EXACT_SIZE, malloc);
	struct cvector *cv = cvector_entry(v);

	ASSERT_EQUAL_PTR(v, cv->data);
	ASSERT_EQUAL(n, cv->size);
	ASSERT_EQUAL(n, cv->allocated);
	check_magic(cv);

	for (uint i = 0; i < n; i++) {
		touch_memory(v[i]);
	}

	cvector_destroy_ext(v, 0, free);
}

struct test_struct {
	uint64 q;
	double w;
	char *e;
};

UTEST(cvector_create_ext2)
{
	const uint n = 7;
	struct test_struct *v = cvector_create_ext(struct test_struct, n,
						   CVECTOR_CREATE_ZERO, NULL);
	struct cvector *cv = cvector_entry(v);

	ASSERT_EQUAL_PTR(v, cv->data);
	ASSERT_EQUAL(n, cv->size);
	ASSERT_GREATER_EQUAL(n, cv->allocated);
	check_magic(cv);

	for (uint i = 0; i < n; i++) {
		touch_memory(v[i]);
	}

	cvector_destroy_ext(v, 0, NULL);
}

int main(int argc, const char **argv)
{
	(void)argc;
	cvector_init();
	unittest(argv);
	cvector_fini();
	return 0;
}

