
#include <stddef.h>
#include <stdint.h>

void	*TLUbzero(void *dst, size_t len)
{
	if (dst == NULL)
		return NULL;
	while (len && (size_t)dst % 8)
	{
		*((unsigned char *)dst) = 0;
		++dst;
		--len;
	}
	if (len >= 8)
	{
		size_t xlen = len / 64;
		while (xlen)
		{
			((uint_fast64_t *)dst)[0] = 0;
			((uint_fast64_t *)dst)[1] = 0;
			((uint_fast64_t *)dst)[2] = 0;
			((uint_fast64_t *)dst)[3] = 0;
			((uint_fast64_t *)dst)[4] = 0;
			((uint_fast64_t *)dst)[5] = 0;
			((uint_fast64_t *)dst)[6] = 0;
			((uint_fast64_t *)dst)[7] = 0;
			dst += 64;
			--xlen;
		}
		len %= 64;
		xlen = len / 8;
		while (xlen)
		{
			((uint_fast64_t *)dst)[0] = 0;
			dst += 8;
			--xlen;
		}
		len %= 8;

	}
	while (len)
	{
		*((unsigned char *)dst) = 0;
		++dst;
		--len;
	}
	return dst;
}
