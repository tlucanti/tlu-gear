
#ifndef CVECTOR_INTERNAL_H
#define CVECTOR_INTERNAL_H

#include <container/cvector.h>
#include <core/compiler.h>
#include <core/defs.h>
#include <core/panic.h>
#include <libc/mem.h>

#if CONFIG_CVECTOR_VALIDATION_LAYER
# include <core/color.h>
# include <core/panic.h>
# define CVECTOR_MAGIC 0xdeadbeefdeadbeef
#endif

#define cvector_entry(ptr) container_of(ptr, struct cvector, data)

struct cvector {
	uint64 allocated;
	uint64 size;
#if CONFIG_CVECTOR_VALIDATION_LAYER
	uint64 magic;
#endif
	__aligned(8) uint8 data[];
};

extern void *malloc(uint64 size);
extern void free(void *ptr);

#ifdef CONFIG_DEBUG
# define INTERNAL __used noinline
#else
# define INTERNAL static
#endif

uint64 allocation_grid_upper(uint64 size);
void check_magic(const struct cvector *cvector);

#endif /* CVECTOR_INTERNAL_H */

