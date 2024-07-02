
#ifndef LIBC_MEM_H
#define LIBC_MEM_H

#include <core/types.h>

const void *tlu_memchr(const void *vp, unsigned char c);
const void *tlu_memnchr(const void *vp, unsigned char c, uint64 size);
const void *tlu_memnrchr(const void *vp, unsigned char c, uint64 size);
int tlu_memcmp(const void *va, const void *vb, uint64 size);
int tlu_memeq(const void *va, const void *vb, uint64 size);
uint64 tlu_memcnt(const void *vp, unsigned char c, uint64 n);
void tlu_memccpy(void *dst, const void *src, unsigned char c, uint64 size);
void tlu_memcpy(void *dst, const void *src, uint64 size);
void tlu_memset(void *ptr, unsigned char c, uint64 size);
void tlu_memset_secure(void *ptr, unsigned char c, uint64 size);
void tlu_memzero(void *ptr, uint64 size);
void tlu_memzero_secure(void *ptr, uint64 size);

#endif /* LIBC_MEM_H */

