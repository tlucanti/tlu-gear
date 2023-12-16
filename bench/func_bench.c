
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <core/panic.h>
#include <core/barrier.h>

#include <stdio.h>

sig_atomic_t should_stop;

static void timer_handler(int sig)
{
	(void)sig;
	WRITE_ONCE(should_stop, 1);
}

void func_bench(void (*callback)(void *), void *context)
{
	struct itimerval timer;
	unsigned long iter = 0;

	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 0;
	timer.it_value.tv_sec = 1;
	timer.it_value.tv_usec = 0;
	should_stop = 0;

	if (signal(SIGVTALRM, timer_handler) == SIG_ERR) {
		panic("signal set error");
	}

	if (setitimer(ITIMER_VIRTUAL, &timer, NULL)) {
		perror(NULL);
		panic("timer error");
	}

	while (!READ_ONCE(should_stop)) {
		callback(context);
		iter++;
	}

	printf("iter: %lu\n", iter);
}

