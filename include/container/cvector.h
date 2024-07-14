
#ifndef CONTAINER_CVECTOR_H
#define CONTAINER_CVECTOR_H

#include <core/types.h>
#include <core/compiler.h>

typedef enum {
	CVECTOR_CREATE_DEFAULT		= 0,
	CVECTOR_CREATE_EXACT_SIZE	= 1,
	CVECTOR_CREATE_ZERO		= 2,
	CVECTOR_CREATE_ONLY_PREALLOC	= 4,
} cvector_create_flags_t;

typedef enum {
	CVECTOR_COPY_DEFAULT		= 0,
	CVECTOR_COPY_EXACT_SIZE		= 1,
	CVECTOR_COPY_EMPTY		= 8,
} cvector_copy_flags_t;

typedef enum {
	CVECTOR_CREATE_FROM_DEFAULT	= 0,
	CVECTOR_CREATE_FROM_EXACT_SIZE	= 1,
} cvector_create_from_flags_t;

// ====================================================================================================================
void cvector_init(void);
void cvector_fini(void);

// ====================================================================================================================
#define cvector_create(type, size, flags) (type *)__cvector_create(sizeof(type), size, flags)
void cvector_destroy(void *vector);

#define cvector_copy(other, flags) (typeof(other))__cvector_copy(other, sizeof(*(other)), flags)
#define cvector_create_from(begin, end, flags)							\
	({											\
		__cvector_same_type(begin, end);						\
		(typeof(*(begin)) *)__cvector_create_from(begin, end, sizeof(*(begin)), flags);	\
	})
#define cvector_create_from_list(flags, initializer_list)					\
	({											\
		typeof((initializer_list)) *list = (initializer_list);				\
		uint64 size = ARRAY_SIZE(initializer_list);					\
		(typeof(list))__cvector_create_from(list, list + size, sizeof(*list), flags);	\
	})

// ====================================================================================================================
#define cvector_at(vector, idx) (*(typeof(vector))__cvector_at(vector, idx, (vector) + (idx)))
#define cvector_rat(vector, idx) cvector_at(vector, cvector_size(vector) - (idx) - 1)
#define cvector_front(vector) cvector_at(vector, 0)
#define cvector_back(vector) cvector_rat(vector, 0)

// ====================================================================================================================
#define cvector_empty(vector) (cvector_size(vector) == 0)
uint64 cvector_size(const void *vector);
uint64 cvector_capacity(const void *vector);

#define cvector_find(vector, value)					\
	({								\
		typeof(*vector) *res = NULL;				\
		typeof(*vector) *iter;					\
		const typeof(value) _value = value;			\
		cvector_for_each(vector, iter) {			\
			if (tlu_memeq(iter, &_value, sizeof(_value))) {	\
				res = iter;				\
				break;					\
			}						\
		}							\
		res;							\
	})

#define cvector_rfind(vector, value)					\
	({								\
		typeof(*vector) *res = NULL;				\
		typeof(*vector) *iter;					\
		const typeof(value) _value = value;			\
		cvector_for_each_reverse(vector, iter)			\
		{							\
			if (tlu_memeq(iter, &_value, sizeof(_value))) {	\
				res = iter;				\
				break;					\
			}						\
		}							\
		res;							\
	})

#define cvector_contains(vector, value) (cvector_find(vector, value) != NULL)

#define cvector_count(vector, value)					\
	({								\
		uint64 res = 0;						\
		typeof(*vector) *iter;					\
		const typeof(value) _value = value;			\
		cvector_for_each(vector, iter) {			\
			if (tlu_memeq(iter, &_value, sizeof(_value))) {	\
				res++;					\
			}						\
		}							\
		res;							\
	})

// ====================================================================================================================
#define cvector_insert(vptr, iter, value)						\
	({										\
		__cvector_same_type(*vptr, iter);					\
		typeof(iter) ret = __cvector_insert(vptr, sizeof(*(iter)), iter);	\
		if (!PTR_ERR(ret)) {							\
			*ret = (value);							\
		}									\
		ret;									\
	})
#define cvector_push_front(vptr, value) cvector_insert(vptr, cvector_begin(*(vptr)), value)
#define cvector_push_back(vptr, value) cvector_insert(vptr, cvector_end(*(vptr)), value)

#define cvector_erase(vptr, iter)						\
	({									\
		__cvector_same_type(*vptr, iter);				\
		(typeof(iter))__cvector_erase(vptr, sizeof(*iter), iter);	\
	})
#define cvector_pop_front(vptr) cvector_erase(vptr, cvector_begin(*(vptr)))
#define cvector_pop_back(vptr) cvector_erase(vptr, cvector_rbegin(*(vptr)))

#define cvector_extend(vptr, vector)					\
	({								\
		__cvector_same_type(*vptr, vector);			\
		__cvector_extend(vptr, vector, sizeof(*vector));	\
	})

// ====================================================================================================================
#define cvector_begin(vptr) (vptr)
#define cvector_end(vptr) ((vptr) + cvector_size(vptr) - 1)
#define cvector_cbegin(vptr) (const typeof(*vptr) *)cvector_begin(vptr)
#define cvector_cend(vptr) (const typeof(*vptr) *)cvector_end(vptr)

#define cvector_rbegin(vptr) ((vptr) + cvector_size(vptr))
#define cvector_rend(vptr) ((vptr) - 1)
#define cvector_crbegin(vptr) (const typeof(*vptr) *)cvector_rbegin(vptr)
#define cvector_crend(vptr) (const typeof(*vptr) *)cvector_rend(vptr)

// ====================================================================================================================

extern void *__cvector_create(uint type_size, uint64 size, cvector_create_flags_t flags);
extern void *__cvector_copy(const void *vec, uint type_size, cvector_copy_flags_t flags);
extern void *__cvector_create_from(const void *begin, const void *end, uint type_size, cvector_create_from_flags_t flags);

extern void *__cvector_at(void *vector, uint64 idx, void *ret);
extern void *__cvector_insert(void **vptr, uint type_size, void *pos);
extern void *__cvector_erase(void **vptr, uint type_size, void *pos);

#define __cvector_same_type(ptr1, ptr2) (void)((ptr1) == (ptr2))

#endif /* CONTAINER_CVECTOR_H */

