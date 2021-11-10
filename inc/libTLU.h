
#ifndef LIBTLU_H
# define LIBTLU_H


void	*TLUmemset(void *dst, unsigned char c, size_t len)
			__attribute__((__nothrow__));

void	*TLUbzero(void *dst, size_t len)
			__attribute__((__nothrow__));


#endif // LIBTLU_H
