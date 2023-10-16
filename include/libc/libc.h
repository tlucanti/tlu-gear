
#include <stddef.h>
#include <stdbool.h>

void tlu_memset(void *ptr, unsigned char chr, size_t size);
void tlu_bzero(void *ptr, size_t size);
int tlu_memcmp(const void *va, const void *vb, size_t size);
bool tlu_memeq(const void *va, const void *vb, size_t size);
const void *tlu_memnchr(const void *vp, unsigned char c, size_t n);
const void *tlu_memchr(const void *vp, unsigned char c);

