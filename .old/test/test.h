
#ifndef TEST_H
# define TEST_H

# include <string.h>
# include <stdio.h>
# include <time.h>
# include <stdlib.h>

# include "color.h"
# include "../inc/libTLU.h"

int digit_num(size_t n)
{
	if (n == 0)
		return (1);
	int ans = 0;
	while (n)
	{
		n /= 10;
		++ans;
	}
	return (ans);
}

long randint(long min, long max)
{
	return (min + rand() % (max - min + 1));
}

void error(const unsigned char *my, const unsigned char *gnu, long size,
	int bp)
{
#ifdef SILENT
	return;
#endif // NOVERBOSE

	int field_size;
	long error_cnt = 0;
	for (long i=0; i < size; ++i)
	{
		if (my[i] != gnu[i])
		{
			++error_cnt;
			field_size = digit_num(i);
		}
	}
	if (field_size < 2)
		field_size = 2;
	printf(TERM_RED "[FAIL] %lu" TERM_WHITE " errors in case "
		TERM_YELLOW "%p %p" TERM_WHITE " of size " TERM_BLUE "%lu"
		TERM_RESET "\n", error_cnt, my, gnu, size);
	printf(INFO "[INFO]" TERM_WHITE
		" set brakepoint in position %d to catch errors" RESET "\n", bp);

#ifdef NOVERBOSE
	return;
#endif // NOVERBOSE


	printf("idx: ");
	long last_wrong = -1;
	for (long i=0; i < size; ++i)
	{
		if (my[i] == gnu[i])
			continue;
		if (last_wrong == -1)
		{
			last_wrong = i - 3;
			if (last_wrong < -1)
				last_wrong = -1;
			if (last_wrong >= 0)
				printf("%*s", field_size, "..");
		}
		if (i - last_wrong >= 6)
		{
			printf(
				" %0*lu %0*lu %*s %0*lu %0*lu " TERM_RED "%0*lu" TERM_RESET,
				field_size, last_wrong + 1,
				field_size, last_wrong + 2,
				field_size, "..",
				field_size, i - 2,
				field_size, i - 1,
				field_size, i
			);
		}
		else if (i - last_wrong >= 5)
		{
			printf(
				" %0*lu %0*lu %0*lu %0*lu " TERM_RED "%0*lu" TERM_RESET,
				field_size, last_wrong + 1,
				field_size, last_wrong + 2,
				field_size, i - 2,
				field_size, i - 1,
				field_size, i
			);
		}
		else if (i - last_wrong >= 4)
		{
			printf(
				" %0*lu %0*lu %0*lu " TERM_RED "%0*lu" TERM_RESET,
				field_size, last_wrong + 1,
				field_size, i - 2,
				field_size, i - 1,
				field_size, i
			);
		}
		else if (i - last_wrong >= 3)
		{
			printf(
				" %0*lu %0*lu " TERM_RED "%0*lu" TERM_RESET,
				field_size, i - 2,
				field_size, i - 1,
				field_size, i
			);
		}
		else if (i - last_wrong >= 2)
		{
			printf(
				" %0*lu " TERM_RED "%0*lu" TERM_RESET,
				field_size, i - 1,
				field_size, i
			);
		}
		else if (i - last_wrong >= 1)
		{
			printf(
				TERM_RED " %0*lu" TERM_RESET,
				field_size, i
			);
		}
		last_wrong = i;
	}
	if (last_wrong != -1 && last_wrong + 1 < size)
		printf(" %0*lu", field_size, last_wrong + 1);
	if (last_wrong != -1 && last_wrong + 2 < size)
		printf(" %0*lu", field_size, last_wrong + 2);
	if (last_wrong != -1 && last_wrong + 3 < size)
		printf(" %*s", field_size, "..");
	printf("\n");


	printf("you: ");
	last_wrong = -1;
	for (long i=0; i < size; ++i)
	{
		if (my[i] == gnu[i])
			continue;
		if (last_wrong == -1)
		{
			last_wrong = i - 3;
			if (last_wrong < -1)
				last_wrong = -1;
			if (last_wrong >= 0)
				printf("%*s", field_size, "..");
		}
		if (i - last_wrong >= 6)
		{
			printf(
				" %0*X %0*X %*s %0*X %0*X " TERM_RED "%0*X" TERM_RESET,
				field_size, my[last_wrong + 1],
				field_size, my[last_wrong + 2],
				field_size, "..",
				field_size, my[i - 2],
				field_size, my[i - 1],
				field_size, my[i]
			);
		}
		else if (i - last_wrong >= 5)
		{
			printf(
				" %0*X %0*X %0*X %0*X " TERM_RED "%0*X" TERM_RESET,
				field_size, my[last_wrong + 1],
				field_size, my[last_wrong + 2],
				field_size, my[i - 2],
				field_size, my[i - 1],
				field_size, my[i]
			);
		}
		else if (i - last_wrong >= 4)
		{
			printf(
				" %0*X %0*X %0*X " TERM_RED "%0*X" TERM_RESET,
				field_size, my[last_wrong + 1],
				field_size, my[i - 2],
				field_size, my[i - 1],
				field_size, my[i]
			);
		}
		else if (i - last_wrong >= 3)
		{
			printf(
				" %0*X %0*X " TERM_RED "%0*X" TERM_RESET,
				field_size, my[i - 2],
				field_size, my[i - 1],
				field_size, my[i]
			);
		}
		else if (i - last_wrong >= 2)
		{
			printf(
				" %0*X " TERM_RED "%0*X" TERM_RESET,
				field_size, my[i - 1],
				field_size, my[i]
			);
		}
		else if (i - last_wrong >= 1)
		{
			printf(
				TERM_RED " %0*X" TERM_RESET,
				field_size, my[i]
			);
		}
		last_wrong = i;
	}
	if (last_wrong != -1 && last_wrong + 1 < size)
		printf(" %0*X", field_size, my[last_wrong + 1]);
	if (last_wrong != -1 && last_wrong + 2 < size)
		printf(" %0*X", field_size, my[last_wrong + 2]);
	if (last_wrong != -1 && last_wrong + 3 < size)
		printf(" %*s", field_size, "..");
	printf("\n");


	printf("gnu: ");
	last_wrong = -1;
	for (long i=0; i < size; ++i)
	{
		if (my[i] == gnu[i])
			continue;
		if (last_wrong == -1)
		{
			last_wrong = i - 3;
			if (last_wrong < -1)
				last_wrong = -1;
			if (last_wrong >= 0)
				printf("%*s", field_size, "..");
		}
		if (i - last_wrong >= 6)
		{
			printf(
				" %0*X %0*X %*s %0*X %0*X " TERM_RED "%0*X" TERM_RESET,
				field_size, gnu[last_wrong + 1],
				field_size, gnu[last_wrong + 2],
				field_size, "..",
				field_size, gnu[i - 2],
				field_size, gnu[i - 1],
				field_size, gnu[i]
			);
		}
		else if (i - last_wrong >= 5)
		{
			printf(
				" %0*X %0*X %0*X %0*X " TERM_RED "%0*X" TERM_RESET,
				field_size, gnu[last_wrong + 1],
				field_size, gnu[last_wrong + 2],
				field_size, gnu[i - 2],
				field_size, gnu[i - 1],
				field_size, gnu[i]
			);
		}
		else if (i - last_wrong >= 4)
		{
			printf(
				" %0*X %0*X %0*X " TERM_RED "%0*X" TERM_RESET,
				field_size, gnu[last_wrong + 1],
				field_size, gnu[i - 2],
				field_size, gnu[i - 1],
				field_size, gnu[i]
			);
		}
		else if (i - last_wrong >= 3)
		{
			printf(
				" %0*X %0*X " TERM_RED "%0*X" TERM_RESET,
				field_size, gnu[i - 2],
				field_size, gnu[i - 1],
				field_size, gnu[i]
			);
		}
		else if (i - last_wrong >= 2)
		{
			printf(
				" %0*X " TERM_RED "%0*X" TERM_RESET,
				field_size, gnu[i - 1],
				field_size, gnu[i]
			);
		}
		else if (i - last_wrong >= 1)
		{
			printf(
				TERM_RED " %0*X" TERM_RESET,
				field_size, gnu[i]
			);
		}
		last_wrong = i;
	}
	if (last_wrong != -1 && last_wrong + 1 < size)
		printf(" %0*X", field_size, gnu[last_wrong + 1]);
	if (last_wrong != -1 && last_wrong + 2 < size)
		printf(" %0*X", field_size, gnu[last_wrong + 2]);
	if (last_wrong != -1 && last_wrong + 3 < size)
		printf(" %*s", field_size, "..");
	printf("\n");
}

void result(long all, long ok)
{
	if (all == ok)
		printf("  ✅  " OK "[%ld/%ld] all test passed 😎\n" RESET, ok, all);
	else if (ok >= all * 9 / 10)
		printf("  ⚠️   " TERM_YELLOW "[%ld/%ld] tests passed 🤔" RESET "\n", ok, all);
	else
		printf("  ⛔️   " TERM_RED "[%ld/%ld]" TERM_WHITE " tests passed 😡💢" RESET "\n", ok, all);
}

void fill(void *array, long size)
{
	unsigned char *a = (unsigned char *)array;
	for (long i=0; i <size; ++i)
		a[i] = (unsigned char)rand();
}

void prompt()
{
	printf(TERM_GREEN "       ╭──────────────────────╮" RESET "\n");
	printf(TERM_GREEN "       │ RUNNING %d BIT TESTS │" RESET "\n", BIT);
	printf(TERM_GREEN "       ╰──────────────────────╯" RESET "\n");
}

#endif
