/**
 *	Author:		antikostya
 *	Created:	2021-11-14 22:55:43
 *	Modified:	2021-11-14 23:33:22
 **/

#include <stddef.h>
#include <immintrin.h>
#include <stdio.h>

void    *TLUmemset(void *dst, unsigned char c, size_t len)
{
    if (dst == NULL)
        return NULL;
    while (len && (size_t)dst % 64)
    {
		printf("aligning %ld\n", (size_t)dst % 64);
        *((unsigned char *)dst) = c;
        ++dst;
        --len;
    }
    while (len >= 64)
    {
		printf("_mm512_store_epi64\n\n");
		_mm512_store_epi64(dst, _mm512_set1_epi8(c));
        dst += 64;
        len -= 64;
    }
    while (len >= 32)
    {
		printf("_mm256_store_epi64\n\n");
		_mm256_store_epi64(dst, _mm256_set1_epi8(c));
        dst += 32;
        len -= 32;
    }
    while (len >= 16)
    {
		printf("_mm_store_epi64\n\n");
        _mm_store_epi64(dst, _mm_set1_epi8(c));
        dst += 16;
        len -= 16;
    }
    while (len)
    {
        *((unsigned char *)dst) = c;
        ++dst;
        --len;
    }
}
