
#include <container/cvector.h>

#define CONFIG_CONTAINER_ALLOC_FAIL 1
#define nosys panic("TODO: not implemented");

__may_alloc
int cvector_init(struct cvector *cvector, unsigned long element_size, unsigned long size)
{
	cvector->element_size = element_size;
	cvector->data = tlu_malloc(size * element_size);

	if (unlikely(cvector->data == NULL)) {
#if CONFIG_CONTAINER_ALLOC_FAIL == 1
		panic("(cvector): no memory to allocate");
#else
		return TLU_ENOMEM;
#endif
	}

	cvector->alloc = size * element_size;
	cvector->size = size;
	tlu_memzero(cvector->data, cvector->alloc);
	return 0;
}

void cvector_destroy(struct cvector *cvector)
{
	tlu_free(cvector->data);
}

const void *cvector_data(const struct cvector *cvector)
{
	return cvector->data;
}

unsigned long cvector_element_size(const struct cvector *cvector)
{
	return cvector->element_size;
}

unsigned long cvector_size(const struct cvector *cvector)
{
	return cvector->size;
}

unsigned long cvector_alloc(const struct cvector *cvector)
{
	return cvector->alloc;
}

void *cvector_at(const struct cvector *cvector, long pos)
{
	if (pos < 0) {
		panic_on((unsigned long)(-pos) > cvector->size, "(cvector): out of bounds");
		pos = cvector->size + pos;
	} else {
		panic_on((unsigned long)pos >= cvector->size, "(cvector): out of bounds");
	}

	return cvector->data + pos * cvector->element_size;
}

