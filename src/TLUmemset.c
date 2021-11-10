
#include <stddef.h>
#include <stdint.h>

void	*TLUmemset(void *dst, unsigned char c, size_t len)
{
	if (dst == NULL)
		return NULL;
	while (len && (size_t)dst % 8)
	{
		*((unsigned char *)dst) = c;
		++dst;
		--len;
	}
	if (len >= 8)
	{
		uint_fast64_t	cccc = c;
		cccc |= cccc << 8;
		cccc |= cccc << 16;
		cccc |= cccc << 32;
		size_t xlen = len / 64;
		while (xlen)
		{
			((uint_fast64_t *)dst)[0] = cccc;
			((uint_fast64_t *)dst)[1] = cccc;
			((uint_fast64_t *)dst)[2] = cccc;
			((uint_fast64_t *)dst)[3] = cccc;
			((uint_fast64_t *)dst)[4] = cccc;
			((uint_fast64_t *)dst)[5] = cccc;
			((uint_fast64_t *)dst)[6] = cccc;
			((uint_fast64_t *)dst)[7] = cccc;
			dst += 64;
			--xlen;
		}
		len %= 64;
		xlen = len / 8;
		while (xlen)
		{
			((uint_fast64_t *)dst)[0] = cccc;
			dst += 8;
			--xlen;
		}
		len %= 8;

	}
	while (len)
	{
		*((unsigned char *)dst) = c;
		++dst;
		--len;
	}
	return dst;
}
