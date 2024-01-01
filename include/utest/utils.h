
#ifndef _UTEST_UTILS_H_
#define _UTEST_UTILS_H_

#include <core/color.h>

#include <stdint.h>
#include <unistd.h>

void *utest_malloc(size_t size);
void utest_random_init(uint32_t seed);
uint64_t utest_random(void);
uint64_t utest_random_range(uint64_t from, uint64_t to);

void utest_progress_start(void);
void utest_progress(unsigned long current, unsigned long total);
void utest_progress_done(void);
void utest_ok(void);

#define __utest_print_color(color, format, ...)                           \
	do {                                                              \
		if (CONFIG_COLOR_OUTPUT && isatty(STDOUT_FILENO)) { \
			printf(color format ANSI_NORMAL, ##__VA_ARGS__);  \
		} else {                                                  \
			printf(format, ##__VA_ARGS__);                    \
		}                                                         \
	} while (false)

#define utest_print_green(format, ...) __utest_print_color(ANSI_BGREEN, format, ##__VA_ARGS__)
#define utest_print_yellow(format, ...) __utest_print_color(ANSI_BYELLOW, format, ##__VA_ARGS__)
#define utest_print_red(format, ...) __utest_print_color(ANSI_BRED, format, ##__VA_ARGS__)
#define utest_print_blue(format, ...) __utest_print_color(ANSI_BBLUE, format, ##__VA_ARGS__)
#define utest_print_cyan(format, ...) __utest_print_color(ANSI_BCYAN, format, ##__VA_ARGS__)
#define utest_print_magenta(format, ...) __utest_print_color(ANSI_BMAGENTA, format, ##__VA_ARGS__)

#define print_purple print_magenta


#endif /* _UTEST_UTILS_H_ */

