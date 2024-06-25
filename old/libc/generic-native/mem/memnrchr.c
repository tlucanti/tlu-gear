
#include <libc/mem.h>

const void *tlu_memnrchr(const void *vp, unsigned char c, size_t n)
{
	 const unsigned char *p = vp;

	 for (long i = n - 1; i >= 0; --i) {
		 if (p[i] == c) {
			 return &p[i];
		 }
	 }
	 return NULL;
}
