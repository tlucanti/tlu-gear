
#ifndef CORE_CONSOLE_H
#define CORE_CONSOLE_H

#include <core/types.h>

int64 tlu_console_write(const void *ptr, uint64 size);

uint tlu_console_puts(const char *str);
uint tlu_console_putc(char c);

uint tlu_console_putn(int64 n);
uint tlu_console_putu(uint64 n);

#endif /* CORE_CONSOLE_H */

