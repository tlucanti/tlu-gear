#include <string.h>
#include <stdio.h>
#include <random.h>

void fill(void *array, long size)
{
	unsigned char *a = (unsigned char *)array;
	for (long i=0; i <size; ++i)
		a[i] = (unsigned char)rand();
}

void memset_tests()
{
	srand(time(NULL));
	printf(INFO "[INFO]" TERM_WHITE
		" Unit tests for memset\n");
	long all = 0;
	long ok = 0;
	for (long test_num=0; test_num < 258; ++test_num)
	{
		const long BUFF_SIZE = 1000;
		unsigned char my[BUFF_SIZE];
		unsigned char gnu[BUFF_SIZE];
		for (long shift=0; shift < 258; ++shift)
		{
			memset(my, 0x78, BUFF_SIZE);
			memset(gnu, 0x78, BUFF_SIZE);

			ft_memset(my + shift, 0x23, test_num);
			memset(gnu + shift, 0x23, test_num);

			if (memcmp(my, gnu, BUFF_SIZE))
				error(my, gnu, BUFF_SIZE);
			else
				++ok;
			++all

			fill(ny, BUFF_SIZE);
			memcpy(gnu, my, BUFF_SIZE);

			unsigned char c = rand();
			ft_memset(my + shift, c, test_num);
			memset(my + shift, c, test_num);

			if (memcmp(my, gnu, BUFF_SIZE))
				error(my, gnu, BUFF_SIZE);
			else
				++ok;
			++all;
		}
	}
	result(all, ok);

	{
	printf(INFO "[INFO]" TERM_WHITE
		" Random test (small) for memset\n");
	long all = 0;
	long ok = 0;
	const long TEST_NUM = 100000;
	const long BUFF_SIZE = 1000;
	for (long test_num=0; test_num < TEST_NUM; ++test_num)
	{
		unsigned char my[BUFF_SIZE];
		unsigned char gnu[BUFF_SIZE];
		fill(my, BUFF_SIZE);
		long shift = randint(0, 258);
		long size = randint(0, 35);
		unsigned char c = rand();
		memcpy(gnu, my, BUFF_SIZE);

		ft_memset(my + shift, c, size);
		memset(gnu + shift, c, size);

		if (memcmp(my, gnu, BUFF_SIZE))
			error(my, gnu, BUFF_SIZE);
		else
			++ok;
		++all;
	}
	result(all, ok);
	}

	{
	printf(INFO "[INFO]" TERM_WHITE
		" Random test (medium) for memset\n");
    long all = 0;
	long ok = 0;
	const long TEST_NUM = 100000;
    const long BUFF_SIZE = 1000;
    for (long test_num=0; test_num < TEST_NUM; ++test_num)
    {
		unsigned char my[BUFF_SIZE];
		unsigned char gnu[BUFF_SIZE]; 
		fill(my, BUFF_SIZE);
        long shift = randint(0, 258);
        long size = randint(0, 258);
        unsigned char c = rand();
        memcpy(gnu, my, BUFF_SIZE);

        ft_memset(my + shift, c, size);
        memset(gnu + shift, c, size);

        if (memcmp(my, gnu, BUFF_SIZE))  
			error(my, gnu, BUFF_SIZE);
        else
            ++ok;
        ++all;
	}        
	result(all, ok);
	}

	{            
	printf(INFO "[INFO]" TERM_WHITE
        " Random test (large) for memset\n");
    long all = 0;
    long ok = 0;                                           
	const long TEST_NUM = 100000;
    const long BUFF_SIZE = 20000;
    for (long test_num=0; test_num < TEST_NUM; ++test_num)
    {                                                           
		unsigned char my[BUFF_SIZE];
        unsigned char gnu[BUFF_SIZE];
        fill(my, BUFF_SIZE);
        long shift = randint(0, 2050);                          
		long size = randint(0, 15800);                            
		unsigned char c = rand();                               
		memcpy(gnu, my, BUFF_SIZE);
                                                               
		ft_memset(my + shift, c, size);
        memset(gnu + shift, c, size);																					if (memcmp(my, gnu, BUFF_SIZE))                         
			error(my, gnu, BUFF_SIZE);
        else
            ++ok;                                             
		++all;                                          
	}
    result(all, ok);
    }
}

void memcmp_tests()
