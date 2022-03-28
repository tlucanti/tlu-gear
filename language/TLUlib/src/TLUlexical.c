
#include <TLUlexical.h>
#include <TLUstring.h>
#include <TLUnistd.h>

# define __INT_STR__(__x) #__x
# define INT_STR(__x) __INT_STR__(__x)

__WUR
intmax_t _TLUs2num(const char *str, lexical_cast_errors *error_ptr, int base)
/*
    string to integer converter
*/
{
    intmax_t        ret_val = 0;
    unsigned int    sign    = 0;

    _TLUassert(base >= 2 and base <= 32);
    if (error_ptr)
        *error_ptr = ok;
    while (_TLUisspace(*str))
        ++str;
    while (*str == '+' or *str == '-')
        if (*str++ == '-')
            sign ^= 1;
    while (_TLUisalnum(*str))
    {
        long long int i;
        if (_TLUisdigit(*str))
            i = *str - '0'; // '0' = 48
        else if (_TLUislower(*str))
            i = *str - 87; // 'a' = 87 + 0xA = 97
        else
            i = *str - 55; // 'A' = 55 + 0xA = 65
        if (i >= base)
        {
            if (error_ptr)
                *error_ptr = bad_base_symbol;
            return 0;
        }
        ret_val = ret_val * base + i;
        if (ret_val < 0)
        {
            if (error_ptr)
                *error_ptr = (lexical_cast_errors)(overflow | sign); // overflow, or underflow if sign == 1
            return LONG_LONG_MAX + sign; // MAX if sign == 1 else MAX + 1 = MIN
        }
        ++str;
    }
    if (*str == 0)
        return ret_val * (((1 - sign) << 1) - 1);
    else if (error_ptr)
        *error_ptr = bad_symbol;
    return 0;
}

static char *unum2s(unsigned long long int val, char *dest, int base, int upper)
{
    _TLUassert(base >= 2 and base <= 32);
    static const char *_lower = "0123456789abcdefghijklmnopqrstuvwxyz";
    static const char *_upper = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *alpha = _lower;

    if (val == 0)
    {
        *dest = '0';
        dest[1] = 0;
        return dest;
    }
    char buf[65];
    int i = 64;
    buf[i] = 0;
    if (upper)
        alpha = _upper;
    while (val)
    {
        buf[--i] = alpha[val % base];
        val /= base;
    }
    return (char *)_TLUmemcpy(dest, buf + i, 65 - i);
}

char *_TLUnum2s(intmax_t val, char *dest, int base, int upper)
{
    _TLUassert(base >= 2 and base <= 32);

    if (val == LONG_LONG_MIN)
        return _TLUstrcpy(dest, INT_STR(LONG_LONG_MIN));
    if (val < 0)
    {
        *dest = '-';
        unum2s(-val, dest + 1, base, upper);
        return dest;
    }
    return unum2s(val, dest, base, upper);
}
