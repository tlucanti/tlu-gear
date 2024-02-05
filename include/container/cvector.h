
#ifndef _CONTAINER_VECTOR_H_
#define _CONTAINER_VECTOR_H_

#include <stdbool.h>

#include <core/compiler.h>

struct cvector {
	unsigned long element_size;
	unsigned long size;
	unsigned long alloc;
	void *data;
};

#define CVECTOR_INIT(__els)                                                \
	(struct cvector){                                                  \
		.element_size = __els, .size = 0, .alloc = 0, .data = NULL \
	};

#if CONFIG_CONTAINER_ALLOC_FAIL && !defined(__may_alloc)
# define __may_alloc __must_check
#else
# define __may_alloc /* empty */
#endif

#define __DEBATING __unused
#define __TODO __unused

/**
 * constructors and destructors
 */
__may_alloc int cvector_init(struct cvector *cvector, unsigned long element_size);
void cvector_destroy(struct cvector *cvector);

/**
 * string informaion
 */
const void *cvector_data(const struct cvector *cvector);
unsigned long cvector_element_size(const struct cvector *cvector);
unsigned long cvector_size(const struct cvector *cvector);
unsigned long cvector_alloc(const struct cvector *cvector);
void *cvector_at(const struct cvector *cvector, long pos);

/**
 * string moditication
 */
void cvector_set(struct cvector *cvector, long pos, const void *val) __DEBATING;
__may_alloc int cvector_append(struct cvector *cvector, const void *val) __TODO;
__may_alloc int cvector_appfront(struct cvector *cvector, const void *val) __TODO;
__may_alloc int cvector_extend(struct cvector *cvector, const struct cvector *other) __TODO;
__may_alloc int cvector_extfront(struct cvector *cvector, const struct cvector *other) __TODO;
__may_alloc int cvector_remove_suffix(struct cvector *cvector, unsigned long size) __TODO;
__may_alloc int cvector_remove_prefix(struct cvector *cvector, unsigned long size) __TODO;

/**
 * string creation
 */
__may_alloc int cvector_copy(const struct cvector *src, struct cvector *dst) __DEBATING;
__may_alloc int cvector_subs(const struct cvector *src, const struct cvector *dst, unsigned long begin, unsigned long end) __DEBATING;

/**
 * string lookups
 */
bool cvector_contains(const struct cvector *cvector, const void *val) __TODO;
unsigned long cvector_count(const struct cvector *cvector, const void *val) __TODO;
void *cvector_find(const struct cvector *cvector, const void *val) __TODO;
void *cvector_rfind(const struct cvector *cvector, const char *pattern) __TODO;

/**
 * cvector formatting
 */
__may_alloc int cvector_replace(struct cvector *cvector, const char *from, const char *to) __DEBATING;
void cvector_reverse(struct cvector *cvector) __TODO;

/**
 * cvector iteration
 */

struct cvector_iterator {
	void *data;
	unsigned long element_size;
};

void cvector_begin(const struct cvector *cvector, struct cvector_iterator *iterator) __TODO;
void cvector_end(const struct cvector *cvector, struct cvector_iterator *iterator) __TODO;
void cvector_next(const struct cvector *cvector, struct cvector_iterator *iterator) __TODO;
void cvector_prev(const struct cvector *cvector, struct cvector_iterator *iterator) __TODO;

#endif /* _CONTAINER_VECTOR_H_ */

