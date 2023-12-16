
#include <libc/char.h>

#define LOWCASE_BITS 0x5u
#define LOWCASE (0x1u << LOWCASE_BITS)
#define UPPER ~LOWCASE

#define NR_DIGITS 10u
#define NR_CHARS 26u

inline unsigned char tlu_toupper_unsafe(unsigned char c)
{
	return c & UPPER;
}

inline unsigned char tlu_tolower_unsafe(unsigned char c)
{
	return c | LOWCASE;
}

inline unsigned char tlu_toupper(unsigned char c)
{
	return c & ~(tlu_islower(c) << LOWCASE_BITS);
}

inline unsigned char tlu_tolower(unsigned char c)
{
	return c | (tlu_isupper(c) << LOWCASE_BITS);
}

inline bool tlu_isdigit(unsigned char c)
{
	return (unsigned char)(c - '0') < NR_DIGITS;
}

inline bool tlu_isupper(unsigned char c)
{
	return (unsigned char)(c - 'A') < NR_CHARS;
}

inline bool tlu_islower(unsigned char c)
{
	return (unsigned char)(c - 'a') < NR_CHARS;
}

