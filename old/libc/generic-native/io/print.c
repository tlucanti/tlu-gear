
#include <libc/io.h>

unsigned int print_ushort(unsigned int x)
{
	return print_ushort_to(&tlu_stdout, x);
}

unsigned int print_short(int x)
{
	return print_short_to(&tlu_stdout, x);
}

unsigned int print_uint(unsigned int x)
{
	return print_uint_to(&tlu_stdout, x);
}

unsigned int print_int(int x)
{
	return print_int_to(&tlu_stdout, x);
}

unsigned int print_ulong(unsigned long x)
{
	return print_ulong_to(&tlu_stdout, x);
}

unsigned int print_long(long x)
{
	return print_long_to(&tlu_stdout, x);
}

unsigned int print_nstr(const char *s, unsigned long n)
{
	return print_nstr_to(&tlu_stdout, s, n);
}

unsigned int print_str(const char *s)
{
	return print_str_to(&tlu_stdout, s);
}

