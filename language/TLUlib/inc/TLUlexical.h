
#ifndef TLU_LEXICAL_H
# define LTU_LEXICAL_H

# include <TLUdefs.h>

# /* remove this */ include <stdio.h>

typedef enum e_lexical_cast_errors
{
    ok              = 0b0000,
    bad_symbol      = 0b0110,
    bad_base_symbol = 0b0111,
    neg_unsigned    = 0b0100,
    overflow        = 0b1000,
    underflow       = 0b1001,
}   lexical_cast_errors;

__WUR intmax_t _TLUs2num(const char *str, lexical_cast_errors *__PTR error_ptr, int base);
char *_TLUnum2s(intmax_t val, char *dest, int base, int upper);

#endif /* TLU_LEXICAL_H */
