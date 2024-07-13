
#include "cvector_internal.h"

#if CONFIG_CVECTOR_VALIDATION_LAYER
extern void cvector_panic(const char *message);

#else
__noret INTERNAL
void cvector_panic(const char *message)
{
	tlu_panic(message);
}
#endif

INTERNAL
uint64 allocation_grid_upper(uint64 size)
{
	return size * 3 / 2;
}

INTERNAL
void check_magic(const struct cvector *cvector)
{
#if CONFIG_CVECTOR_VALIDATION_LAYER
	if (cvector->magic != CVECTOR_MAGIC) {
		cvector_panic("cvector: invalid pointer (magic check fail)");
	}
#else
	(void)cvector;
#endif
}

INTERNAL
void check_range(const struct cvector *cvector, uint64 idx)
{
	if (idx >= cvector->size) {
		cvector_panic("cvector: out of range");
	}
}

void cvector_init(void)
{
}

void cvector_fini(void)
{
}

void *__cvector_create(uint type_size, uint64 size, uint flags)
{
	struct cvector *cvector;
	uint64 alloc;

	if (flags & CVECTOR_CREATE_EXACT_SIZE)
		alloc = size;
	else
		alloc = allocation_grid_upper(size);


	cvector = malloc(type_size * alloc + sizeof(struct cvector));
	if (cvector == NULL)
		return NULL;

	cvector->allocated = alloc;
	if (flags & CVECTOR_CREATE_ONLY_PREALLOC)
		cvector->size = 0;
	else
		cvector->size = size;
#if CONFIG_CVECTOR_VALIDATION_LAYER
	cvector->magic = CVECTOR_MAGIC;
#endif

	if (flags & CVECTOR_CREATE_ZERO)
		tlu_memzero(cvector->data, type_size * cvector->size);

	return cvector->data;
}

void cvector_destroy(void *ptr)
{
	struct cvector *cvector = cvector_entry(ptr);

	check_magic(cvector);
	free(cvector);
}

void *__cvector_at(void *ptr, uint64 idx, void *ret)
{
	struct cvector *cvector = cvector_entry(ptr);

	check_magic(cvector);
	check_range(cvector, idx);
	return ret;
}

