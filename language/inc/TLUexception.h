
#ifndef TLU_EXCEPTION_H
# define TLU_EXCEPTION_H

# include <setjmp.h>

# include <TLUdefs.h>
# include <TLUobject.h>
# include <TLUtypeid.h>
# include <TLUbuiltin.h>

typedef enum _TLUexception_types_t
{
    TLU_BASE_EXCEPTION                = 0b11111111111,
    /* */TLU_SYSTEM_EXIT              = 0b10000000000,
    /* */TLU_KEYBOARD_INTERRUPT       = 0b01000000000,
    /* */TLU_EXCEPTION                = 0b00100000000,
    /* * */TLU_ARITHMETIC_ERROR       = 0b00110000000,
    /* * * */TLU_ZERO_DIVISION_ERROR  = 0b00111000000,
    /* * */TLU_ASSERTION_ERROR        = 0b00110100000,
    /* * */TLU_RUNTIME_ERROR          = 0b00110010000,
    /* * * */TLU_RECURSION_ERROR      = 0b00110011000,
    /* * */TLU_TYPE_ERROR             = 0b00110000100,
    /* * */TLU_VALUE_ERROR            = 0b00110000010,
    /* * */TLU_WARNING                = 0b00110000001
} _TLUexception_types;

typedef struct _TLUexception_t
{
    _TLUexception_types   type;
    TLUobject               what;
} _TLUexception;

static __WUR inline const char *__TLUexception_name(_TLUexception_types _type)
{
    switch(_type)
    {
        case TLU_BASE_EXCEPTION:        return "BaseException";
        case TLU_SYSTEM_EXIT:           return "SystemExit";
        case TLU_KEYBOARD_INTERRUPT:    return "KeyboardInterrupt";
        case TLU_EXCEPTION:             return "Exception";
        case TLU_ARITHMETIC_ERROR:      return "ArithmeticError";
        case TLU_ZERO_DIVISION_ERROR:   return "ZeroDivisionError";
        case TLU_ASSERTION_ERROR:       return "AssertionError";
        case TLU_RUNTIME_ERROR:         return "RuntimeError";
        case TLU_RECURSION_ERROR:       return "RecursionError";
        case TLU_TYPE_ERROR:            return "TypeError";
        case TLU_VALUE_ERROR:           return "ValueError";
        case TLU_WARNING:               return "Warning";
        default:                        return "UNKNOWN_EXCEPTION_TYPE";
    }
}

void  __TLU_exception_traceback(TLUobject _exc)
{
    _TLUwrite(2, "uncaught exception of type ", 27);
    if (__IS_EXC(_exc))
    {
        __TLUwrite_str(2, __TLUexception_name(__GET_EXC_TYPE(_exc)));
        _TLUwrite(2, ": ", 2);
        _TLU_print_single(__GET_EXC_WHAT(_exc));
    } \
    else
    {
        __TLU_print_single(_exc);
    }
}

# define ASSERT_NUM(_obj) _ASSERT_TYPE_MACRO(_obj, "num", IS_NUM(_obj))
# define ASSERT_STR(_obj) _ASSERT_TYPE_MACRO_1(_obj, "str", IS_STR(_obj))

#endif /* TLU_EXCEPTION_H */