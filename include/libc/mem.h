
#ifndef LIBC_MEM_H
#define LIBC_MEM_H

#include <core/types.h>

void tlu_memset(void *ptr, unsigned char c, uint64 size);
void tlu_memzero(void *ptr, uint64 size);

#endif /* LIBC_MEM_H */

