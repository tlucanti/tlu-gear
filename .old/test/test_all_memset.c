#include "test.h"

#if TESTFUNC == 1
# define _CALL_TEST1 \
	TLUmemset(my + shift, 0x23, test_num); \
	memset(gnu + shift, 0x23, test_num)
# define _CALL_TEST2 \
	TLUmemset(my + shift, c, test_num); \
	memset(gnu + shift, c, test_num)
# define _CALL_TEST3 \
	TLUmemset(my + shift, c, size); \
	memset(gnu + shift, c, size)

#endif

#if TESTFUNC == 2
# define _CALL_TEST1 \
	TLUbzero(my + shift, test_num); \
	bzero(gnu + shift, test_num)
# define _CALL_TEST2 \
	(void)c; \
	TLUbzero(my + shift, test_num); \
	bzero(gnu + shift, test_num)
# define _CALL_TEST3 \
	(void)c; \
	TLUbzero(my + shift, size); \
	bzero(gnu + shift, size)

#endif

void memset_test()
{
	srand(time(NULL));

	{
		printf(INFO "[INFO]" TERM_WHITE " Unit tests for memset" RESET "\n");
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

				_CALL_TEST1;

				if (memcmp(my, gnu, BUFF_SIZE))
				{
					error(my, gnu, BUFF_SIZE, 1);
					/*
					 * BRAIKPOINT POSITION ( 1 )
					 * SET BRAKEPOINT HERE TO KNOW WHERE IS ERROR 
					 */
#ifdef STOPATERROR
					_CALL_TEST1;
					return;
#endif
				}
				else
					++ok;
				++all;

				fill(my, BUFF_SIZE);
				unsigned char c = rand();
				memcpy(gnu, my, BUFF_SIZE);
				
				_CALL_TEST2;

				if (memcmp(my, gnu, BUFF_SIZE))
				{
					error(my, gnu, BUFF_SIZE, 2);
					/*
					 * BRAIKPOINT POSITION ( 2 )
					 * SET BRAKEPOINT HERE TO KNOW WHERE IS ERROR 
					 */
#ifdef STOPATERROR
					_CALL_TEST2;
					return;
#endif
				}
				else
					++ok;
				++all;
			}
		}
		result(all, ok);
	}

	{
		printf(INFO "[INFO]" TERM_WHITE
			" Random test (small) for memset" RESET "\n");
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

			_CALL_TEST3;

			if (memcmp(my, gnu, BUFF_SIZE))
			{
				error(my, gnu, BUFF_SIZE, 3);
				/*
				 * BRAIKPOINT POSITION ( 3 )
				 * SET BRAKEPOINT HERE TO KNOW WHERE IS ERROR 
				 */
#ifdef STOPATERROR
				_CALL_TEST3;
				return;
#endif
			}
			else
				++ok;
			++all;
		}
		result(all, ok);
	}

	{
		printf(INFO "[INFO]" TERM_WHITE
			" Random test (medium) for memset" RESET "\n");
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

			_CALL_TEST3;

			if (memcmp(my, gnu, BUFF_SIZE))
			{
				error(my, gnu, BUFF_SIZE, 4);
				/*
				 * BRAIKPOINT POSITION ( 4 )
				 * SET BRAKEPOINT HERE TO KNOW WHERE IS ERROR 
				 */
#ifdef STOPATERROR
				_CALL_TEST3;
				return;
#endif
			}
			else
				++ok;
			++all;
		}
		result(all, ok);
	}

	{
		printf(INFO "[INFO]" TERM_WHITE
			" Random test (large) for memset" RESET "\n");
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

			_CALL_TEST3;

			if (memcmp(my, gnu, BUFF_SIZE))
			{
				error(my, gnu, BUFF_SIZE, 5);
				/*
				 * BRAIKPOINT POSITION ( 5 )
				 * SET BRAKEPOINT HERE TO KNOW WHERE IS ERROR 
				 */
#ifdef STOPATERROR
				_CALL_TEST3;
				return;
#endif
			}
			else
				++ok;
			++all;
		}
		result(all, ok);
	}
}

int main()
{
	prompt();
	memset_test();
}
