
#include "cvector_internal.h"

INTERNAL uint64 allocation_grid_upper(uint64 size)
{
	return size * 3 / 2;
}

INTERNAL void check_magic(const struct cvector *cvector)
{
#if CONFIG_CVECTOR_VALIDATION_LAYER
	if (cvector->magic != CVECTOR_MAGIC) {
		tlu_panic("cvector: invalid pointer (magic check fail)");
	}
#else
	(void)cvector;
#endif
}

void cvector_init(void)
{
}

void cvector_fini(void)
{
}

void *__cvector_create(uint type_size, uint64 size, uint flags,
		       allocator_t allocator)
{
	struct cvector *cvector;
	uint64 alloc;

	if (allocator == NULL)
		allocator = malloc;


	if (flags & CVECTOR_CREATE_EXACT_SIZE)
		alloc = size;
	else
		alloc = allocation_grid_upper(size);


	cvector = allocator(type_size * alloc + sizeof(struct cvector));
	if (cvector == NULL)
		return NULL;

	cvector->allocated = alloc;
	cvector->size = size;
#if CONFIG_CVECTOR_VALIDATION_LAYER
	cvector->magic = CVECTOR_MAGIC;
#endif

	if (flags & CVECTOR_CREATE_ZERO)
		tlu_memzero(cvector->data, type_size * alloc);

	return cvector->data;
}

void cvector_destroy_ext(void *ptr, uint flags, destructor_t destructor)
{
	struct cvector *cvector = cvector_entry(ptr);
	(void)flags;

	check_magic(cvector);

	if (destructor == NULL)
		destructor = free;
	destructor(cvector);
}

