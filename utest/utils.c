
#include <core/panic.h>

#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>

void utest_random_init(uint32_t seed)
{
	if (seed ==  0) {
		srandom(time(NULL));
	} else {
		srandom(seed);
	}
}

uint64_t utest_random(void)
{
	uint64_t r1 = random();
	uint64_t r2 = random();

	return r1 | (r2 << 32u);
}

uint64_t utest_random_range(uint64_t from, uint64_t to)
{
	panic_on(from > to, "random invalid args");

	return utest_random() % (to - from + 1) + from;
}

void utest_progress_start(void)
{
	if (!isatty(STDOUT_FILENO)) {
		return;
	}

	printf("   ");
	fflush(stdout);
}

void utest_progress(unsigned long current, unsigned long total)
{
	static unsigned long prev = ULONG_MAX;

	panic_on(current >= total, "too many progress");

	if (!isatty(STDOUT_FILENO)) {
		return;
	}

	current = current * 100 / total;
	if (current != prev) {
		printf("\b\b\b%02lu%%", current);
		fflush(stdout);
		prev = current;
	}
}

void utest_progress_done(void)
{
	if (!isatty(STDOUT_FILENO)) {
		return;
	}

	printf("\b\b\bDONE\b\b\b\b");
	fflush(stdout);
}

