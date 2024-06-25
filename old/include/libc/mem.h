
#ifndef _LIBC_MEM_H_
#define _LIBC_MEM_H_

#include <stddef.h>
#include <stdbool.h>
#include <core/compiler.h>

void tlu_memset(void *ptr, unsigned char chr, size_t size);
void tlu_memset_unaligned(void *ptr, unsigned char chr, size_t size) __DEBATING;
void tlu_memset8(void *ptr, unsigned char chr, size_t size) __DEBATING;
void tlu_memset16(void *ptr, unsigned short val, size_t size) __DEBATING;
void tlu_memset32(void *ptr, unsigned int val, size_t size) __DEBATING;
void tlu_memset64(void *ptr, unsigned long val, size_t size) __DEBATING;

void tlu_memzero(void *ptr, size_t size);
int tlu_memcmp(const void *va, const void *vb, size_t size);
bool tlu_memeq(const void *va, const void *vb, size_t size);
const void *tlu_memnchr(const void *vp, unsigned char c, size_t n);
const void *tlu_memchr(const void *vp, unsigned char c);
const void *tlu_memnrchr(const void *vp, unsigned char c, size_t n) __TODO;
unsigned long tlu_memcnt(const void *vp, unsigned char c, size_t n);
void tlu_memcpy(void *dst, const void *src, size_t size);
void tlu_memmove(void *dst, const void *src, size_t size);

#endif /* _LIBC_MEM_H_ */

