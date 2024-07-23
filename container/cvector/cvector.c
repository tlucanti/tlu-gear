
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
	return max(7u, size * 3 / 2);
}

INTERNAL
struct cvector *realloc_more(struct cvector *old, uint type_size)
{
	uint64 alloc = allocation_grid_upper(old->allocated);
	struct cvector *vec = malloc(alloc * type_size + sizeof(struct cvector));

	if (vec == NULL)
		return NULL;
	tlu_memcpy(vec, old, old->allocated * type_size + sizeof(struct cvector));
	vec->allocated = alloc;

	free(old);
	return vec;
}

INTERNAL
void set_magic(struct cvector *cvector)
{
#if CONFIG_CVECTOR_VALIDATION_LAYER
	cvector->magic = CVECTOR_MAGIC;
#else
	(void)cvector;
#endif
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

void *__cvector_create(uint type_size, uint64 size, cvector_create_flags_t flags)
{
	struct cvector *cvector;
	uint64 alloc;

	if (flags & CVECTOR_CREATE_EXACT_SIZE)
		alloc = size;
	else
		alloc = allocation_grid_upper(size);


	cvector = malloc(type_size * alloc + sizeof(struct cvector));
	if (unlikely(cvector == NULL))
		return NULL;

	set_magic(cvector);
	cvector->allocated = alloc;
	if (flags & CVECTOR_CREATE_ONLY_PREALLOC)
		cvector->size = 0;
	else
		cvector->size = size;

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

void *__cvector_copy(const void *pother, uint type_size, cvector_copy_flags_t flags)
{
	struct cvector *other = cvector_entry(pother);
	struct cvector *copy;
	uint64 alloc;
	uint64 size;

	check_magic(other);
	alloc = other->allocated;
	size = other->size;

	if (flags & CVECTOR_COPY_EXACT_SIZE)
		alloc = size;
	if (flags & CVECTOR_COPY_EMPTY)
		size = 0;

	copy = malloc(type_size * alloc + sizeof(struct cvector));
	if (unlikely(copy == NULL))
		return NULL;

	set_magic(copy);
	copy->allocated = alloc;
	copy->size = size;

	tlu_memcpy(copy->data, other->data, size * type_size);
	return copy->data;
}

void *__cvector_create_from(const void *begin, const void *end, uint type_size, cvector_create_from_flags_t flags)
{
	struct cvector *cvector;
	uint64 alloc;
	uint64 size = (end - begin) / type_size;

	if (unlikely(begin > end))
		cvector_panic("cvector: end iterator less than begin iterator");

	if (flags & CVECTOR_CREATE_FROM_EXACT_SIZE)
		alloc = size;
	else
		alloc = allocation_grid_upper(size);

	cvector = malloc(type_size * alloc + sizeof(struct cvector));
	if (unlikely(cvector == NULL))
		return NULL;

	set_magic(cvector);
	cvector->allocated = alloc;
	cvector->size = size;

	tlu_memcpy(cvector->data, begin, size * type_size);
	return cvector->data;
}

void *__cvector_at(void *ptr, uint64 idx, void *ret)
{
	struct cvector *cvector = cvector_entry(ptr);

	check_magic(cvector);
	if (idx != cvector->size)
		check_range(cvector, idx);

	return ret;
}

extern void *__cvector_insert(void *vvptr, uint type_size, void *pos)
{
	void **vptr = vvptr;
	struct cvector *cvector = cvector_entry(*vptr);
	uint64 idx = (pos - *vptr) / type_size;

	check_magic(cvector);
	if (unlikely(cvector->size == cvector->allocated)) {
		cvector = realloc_more(cvector, type_size);
		if (unlikely(cvector == NULL))
			return NULL;

		*vptr = cvector->data;
		pos = cvector->data + idx * type_size;
	}

	if (cvector->size != idx)
		check_range(cvector, idx);
	tlu_memmove(pos + type_size, pos, (cvector->size - idx) * type_size);
	cvector->size++;

	return pos;
}

bool cvector_empty(const void *ptr)
{
	return cvector_size(ptr) == 0;
}

uint64 cvector_size(const void *ptr)
{
	const struct cvector *cvector = cvector_entry(ptr);

	check_magic(cvector);
	return cvector->size;
}

uint64 cvector_capacity(const void *ptr)
{
	const struct cvector *cvector = cvector_entry(ptr);

	check_magic(cvector);
	return cvector->allocated;
}

