/**
 *	Author:		antikostya
 *	Created:	2021-11-10 23:44:41
 *	Modified:	2021-11-11 00:20:44
 **/

#include "test.h"

#include <ctype.h>

#if TESTFUNC == 1
# define _test_func TLUisdigit
# define _gnu_func isdigit
#endif

#define XOR(a, b) (!(a) != !(b))

static void _error(unsigned char i, int ans)
{
    printf(TERM_RED "[FAIL]" TERM_WHITE " error in case "
        TERM_YELLOW "%3d ", i);
    if (isprint(i) && !isspace(i))
        printf("(%c)" TERM_WHITE ":  ", (unsigned char)i);
    else
        printf("(%02X)" TERM_WHITE ": ", (unsigned char)i);
    printf("answer is ");
    if (ans)
        printf(TERM_PURPLE "True" TERM_WHITE " but you returned "
            TERM_PURPLE "False" RESET "\n");
    else
        printf(TERM_PURPLE "False" TERM_WHITE " but you returned "
            TERM_PURPLE "True" RESET "\n");
}

void is_smth_test()
{
    long all = 0;
    long ok = 0;
    for (int i=0; i < 256; ++i)
    {
        if (XOR(_test_func(i), _gnu_func(i)))
            _error(i, _gnu_func(i));
        else
            ++ok;
        ++all;
    }
    result(all, ok);
}

int main()
{
    prompt();
    is_smth_test();
}
