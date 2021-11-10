
#ifndef LIBTLU_H
# define LIBTLU_H

# define _NOTHROW __attribute__((__nothrow__))
# define _WUR

void	*TLUmemset(void *dst, unsigned char c, size_t len)
			_NOTHROW;

void	*TLUbzero(void *dst, size_t len)
			_NOTHROW;

int TLUisdigit(unsigned char c)
			_WUR _NOTHROW;

#endif // LIBTLU_H
