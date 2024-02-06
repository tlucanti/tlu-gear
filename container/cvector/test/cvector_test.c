
#include <core/math.h>
#include <core/panic.h>
#include <container/cvector.h>
#include <utest/utest.h>

UTEST(cvector_init)
{
	struct cvector a, b = CVECTOR_INIT(sizeof(int));

	cvector_init(&a, sizeof(long), 3);

	cvector_destroy(&a);
	cvector_destroy(&b);
}

UTEST(cvector_element_size)
{
	struct cvector a, b = CVECTOR_INIT(sizeof(int));

	cvector_init(&a, sizeof(long), 0);

	ASSERT_EQUAL(sizeof(long), cvector_element_size(&a));
	ASSERT_EQUAL(sizeof(int), cvector_element_size(&b));
}

UTEST(cvector_data)
{
	struct cvector a, b = CVECTOR_INIT(sizeof(int));

	cvector_init(&a, sizeof(long), 3);

	ASSERT_NOT_NULL(cvector_data(&a));
	ASSERT_NULL(cvector_data(&b));

	cvector_destroy(&a);
	cvector_destroy(&b);
}

UTEST(cvector_size)
{
	struct cvector a, b = CVECTOR_INIT(sizeof(int));

	cvector_init(&a, sizeof(long), 3);

	ASSERT_EQUAL(3, cvector_size(&a));
	ASSERT_EQUAL(0, cvector_size(&b));

	cvector_destroy(&a);
	cvector_destroy(&b);
}

UTEST(cvector_alloc)
{
	struct cvector a, b = CVECTOR_INIT(sizeof(int));

	cvector_init(&a, sizeof(long), 3);

	ASSERT_NOT_ZERO(cvector_alloc(&a));
	ASSERT_ZERO(cvector_alloc(&b));

	cvector_destroy(&a);
	cvector_destroy(&b);
}

UTEST(cvector_at)
{
	struct cvector a, b = CVECTOR_INIT(sizeof(int));

	cvector_init(&a, sizeof(long), 3);
	((long *)a.data)[0] = 1;
	((long *)a.data)[1] = 2;
	((long *)a.data)[2] = 3;

	ASSERT_EQUAL(1, *(long *)cvector_at(&a, 0));
	ASSERT_EQUAL(2, *(long *)cvector_at(&a, 1));
	ASSERT_EQUAL(3, *(long *)cvector_at(&a, 2));
	ASSERT_EQUAL(3, *(long *)cvector_at(&a, -1));
	ASSERT_EQUAL(2, *(long *)cvector_at(&a, -2));
	ASSERT_EQUAL(1, *(long *)cvector_at(&a, -3));

	ASSERT_PANIC(cvector_at(&a, 3));
	ASSERT_PANIC(cvector_at(&b, 0));
	ASSERT_PANIC(cvector_at(&a, -4));
	ASSERT_PANIC(cvector_at(&b, -1));

	cvector_destroy(&a);
	cvector_destroy(&b);
}

int main(int, const char **argv)
{
	unittest(argv);
}

