
#ifndef _UTEST_UTILS_H_
#define _UTEST_UTILS_H_

#include <core/compiler.h>
#include <core/types.h>

void *utest_malloc(uint64 size);

uint64 utest_true_random(void);
uint64 utest_true_random_range(uint64 min, uint64 max);
void utest_random_init(uint seed);
uint64 utest_random(void);
uint64 utest_random_range(uint64 min, uint64 max);
void utest_random_strings(char *a, char *b, uint64 size);
#define utest_random_string(s, size) utest_random_strings(s, s, size)
double utest_random_float(void);
double utest_random_float_uniform(double min, double max);
bool utest_coin_flip(double propability);

void utest_print_mem(const void *exp, const void *real, uint64 size);
void utest_print_str(const char *exp, const char *real);

void utest_progress_start(void);
void utest_progress(uint current, uint total);
void utest_progress2(uint64 inner, uint64 outer, uint64 inner_total, uint64 outer_total);
void utest_progress3(uint64 inner, uint64 middle, uint64 outer,
		     uint64 inner_total, uint64 middle_total, uint64 outer_total);
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

