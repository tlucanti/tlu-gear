
#ifndef _UTEST_UTILS_H_
#define _UTEST_UTILS_H_

#include <core/compiler.h>
#include <core/types.h>

void *utest_malloc(uint64 size);
void utest_random_init(uint seed);
uint64 utest_random(void);
uint64 utest_random_range(uint64 from, uint64 to);
void utest_random_strings(char *a, char *b, uint64 size);

void utest_progress_start(void);
void utest_progress(uint current, uint total);
void utest_progress_done(void);
void utest_ok(void);

__printf(2, 3) int utest_print_color(const char *color, const char *format, ...);
__printf(1, 2) int utest_print_white(const char *format, ...);
__printf(1, 2) int utest_print_red(const char *format, ...);
__printf(1, 2) int utest_print_green(const char *format, ...);
__printf(1, 2) int utest_print_yellow(const char *format, ...);
__printf(1, 2) int utest_print_blue(const char *format, ...);
__printf(1, 2) int utest_print_magenta(const char *format, ...);
__printf(1, 2) int utest_print_cyan(const char *format, ...);
#define print_purple print_magenta

#endif /* _UTEST_UTILS_H_ */

