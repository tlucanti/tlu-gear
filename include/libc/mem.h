
#ifndef LIBC_MEM_H
#define LIBC_MEM_H

#include <core/types.h>

int tlu_memcmp(const void *va, const void *vb, uint64 size);
uint64 tlu_memcnt(const void *vp, unsigned char c, uint64 n);
void tlu_memset(void *ptr, unsigned char c, uint64 size);
void tlu_memset_secure(void *ptr, unsigned char c, uint64 size);
void tlu_memzero(void *ptr, uint64 size);
void tlu_memzero_secure(void *ptr, uint64 size);

#endif /* LIBC_MEM_H */

