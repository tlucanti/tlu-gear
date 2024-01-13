
#ifndef _UTEST_UTILS_H_
#define _UTEST_UTILS_H_

#include <stdint.h>
#include <unistd.h>

void *utest_malloc(size_t size);
char *utest_read_all(int fd, size_t *nr_read);
void utest_random_init(uint32_t seed);
uint64_t utest_random(void);
uint64_t utest_random_range(uint64_t from, uint64_t to);

void utest_progress_start(void);
void utest_progress(unsigned long current, unsigned long total);
void utest_progress_done(void);
void utest_ok(void);

int utest_print_color(const char *color, const char *format, ...);
int utest_print_red(const char *format, ...);
int utest_print_green(const char *format, ...);
int utest_print_yellow(const char *format, ...);
int utest_print_blue(const char *format, ...);
int utest_print_magenta(const char *format, ...);
int utest_print_cyan(const char *format, ...);

#define print_purple print_magenta

#endif /* _UTEST_UTILS_H_ */

