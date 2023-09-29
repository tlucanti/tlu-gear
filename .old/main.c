#include <stdio.h>
#include <immintrin.h>
#include <unistd.h>
#include <string.h>
#include <avx2intrin.h>
#include "inc/libTLU.h"

int main() {
	 const int BUFF_SIZE = 1024;
	__attribute__((aligned(64))) char my[BUFF_SIZE];
	__attribute__((aligned(64))) char gnu[BUFF_SIZE];
	printf("%p %lu\n", my, (size_t)my % 64);
//	memset(my, 0x67, BUFF_SIZE);
	// memset(gnu, 0x67, BUFF_SIZE);
	
	// memset(gnu, 0x23, 16);
//	 TLUmemset(my, 0x23, 64);
	_mm512_store_epi64(my, _mm512_set1_epi8(0x23));
	if (memcmp(my, gnu, BUFF_SIZE) != 0)
	{
		printf("gnu: ");
		for (int i=0; i < BUFF_SIZE; ++i)
			printf("%x ", gnu[i]);
		printf("\nyou: ");
		for (int i=0; i < BUFF_SIZE; ++i)
			printf("%x ", my[i]);
	}
	else
		printf("OK\n");
}
