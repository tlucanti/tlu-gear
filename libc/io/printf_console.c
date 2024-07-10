
#include <core/types.h>
#include <stdio.h>

int64 tlu_console_write(const void *ptr, uint64 size)
{
	return fwrite(ptr, size, 1, stdout);
}

uint tlu_console_puts(const char *str)
{
	return printf("%s", str);
}

uint tlu_console_putc(char c)
{
	return printf("%c", c);
}

uint tlu_console_putn(int64 n)
{
	return printf("%ld", n);
}

uint tlu_console_putu(uint64 n)
{
	return printf("%lu", n);
}

