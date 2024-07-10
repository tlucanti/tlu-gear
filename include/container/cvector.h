
#ifndef CONTAINER_CVECTOR_H
#define CONTAINER_CVECTOR_H

#include <core/types.h>

typedef void *(* allocator_t)(uint64 size);
typedef void (* destructor_t)(void *);

enum cvecor_create_flags {
	CVECTOR_CREATE_EXACT_SIZE = 1,
	CVECTOR_CREATE_ZERO = 2,
	CVECTOR_CREATE_ONLY_PREALLOC = 4,
};

void cvector_init(void);
void cvector_fini(void);

#define cvector_create(type, size) cvector_create_ext(type, size, 0, NULL)
#define cvector_create_ext(type, size, flags, allocator) \
	(type *)__cvector_create(sizeof(type), size, flags, allocator);

#define cvector_destroy(cvector) cvector_destroy_ext(cvector, 0, NULL)
void cvector_destroy_ext(void *cvector, uint flags, destructor_t destructor);

#define cvector_at(cvector, idx) (*(typeof(cvector))__cvector_at(cvector, idx, (cvector) + (idx)))

extern void *__cvector_create(uint type_size, uint64 size, uint flags,
			      allocator_t allocator);
extern void *__cvector_at(void *cvector, uint64 idx, void *ret);

#endif /* CONTAINER_CVECTOR_H */

