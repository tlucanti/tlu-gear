
#ifndef TLU_EXCEPTION_H
# define TLU_EXCEPTION_H

# include <TLUobject.h>
# include <TLUtypeid.h>
# include <TLUbuiltin.h>

typedef struct _TLUexception_t
{
    uintmax_t   type;
    TLUobject   what;
} _TLUexception;

typedef enum _TLUexception_types_t
{
    TLU_BASE_EXCEPTION                  = 0b11111111111,
    /* */TLU_SYSTEM_EXIT                = 0b01000000000,
    /* */TLU_KEYBOARD_INTERRUPT         = 0b01000000001,
    /* */TLU_EXCEPTION                  = 0b00100000000,
    /* * * */TLU_ARITHMETIC_ERROR       = 0b00110000000,
    /* * * * */TLU_ZERO_DIVIZION_ERROR  = 0b00110000001,
    /* * * */TLU_ASSERTATION_ERROR      = 0b00100000001,
    /* * * */TLU_RUNTIME_ERROR          = 0b00101000000,
    /* * * * */TLU_RECURSION_ERROR      = 0b00101000001,
    /* * * */TLU_TYPE_ERROR             = 0b00100000010,
    /* * * */TLU_VALUE_ERROR            = 0b00100000011,
    /* * * */TLU_WARNING                = 0b00100000100
} _TLUexception_types;

void throw();

# define ASSERT_NUM(_obj) _ASSERT_TYPE_MACRO_2(_obj, "num", TLUOBJ_NUM_TYPEID, TLUOBJ_NUM_LONG_TYPEID)
# define ASSERT_STR(_obj) _ASSERT_TYPE_MACRO_1(_obj, "str", TLUOBJ_STR_TYPEID)

# define _ASSERT_TYPE_MACRO_1(_obj, _type, _pred) _ASSERT_TYPE_MACRO ( \
    _obj, _type, (_obj).typeid != (_pred))

# define _ASSERT_TYPE_MACRO_2(_obj, _type, _pred1, _pred2) _ASSERT_TYPE_MACRO ( \
    _obj, _type, (_obj).typeid != (_pred1) && (_obj).typeid != (_pred2))

# define _ASSERT_TYPE_MACRO(_obj, _type, _pred) do { \
    if (_pred) \
        throw(TypeError(format(TLUstr("Expected '" _type "' type, got {}"), TLUstr(TLUtypenames[(_obj).typeid])))); \
} while(0)


#endif /* TLU_EXCEPTION_H */