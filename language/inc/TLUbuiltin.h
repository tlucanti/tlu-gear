
#ifndef TLU_BUILTIN_H
# define TLU_BUILTIN_H

# include "TLUobjstack.h"
# include "../TLUlib/inc/TLUmemory.h"
# include "TLUoperators.h"

# define TLUinit do { \
    _TLUobjstack = _TLUallocator(sizeof(TLUobject) * 162); \
    _TLUobjstack_allocated = 162; \
    TLUfun_begin; \
} while (0)

# define TLUstop do { \
    _TLUobjstack_clear(); \
    _TLUdeallocator(_TLUobjstack); \
} while (0)

inline void sum() {}
inline void print() {}
inline void del() {}
inline void num() {}

# define sum(...) __TLU_call_operator_macro(sum, __VA_ARGS__);
# define print(...) __TLU_call_operator_macro(print, __VA_ARGS__);
# define del(...) __TLU_call_operator_macro(del, __VA_ARGS__);
# define num(...) __TLU_call_operator_macro(num, __VA__ARGS__);

__TLU_add_binary_operator_macro(void, iadd)

__TLU_add_unary_operator_macro(TLUobject, copy)
__TLU_add_unary_operator_macro(TLUobject, str)

TLUobject  _TLU_sum(TLUobject *__PTR args) __NOTHROW;
TLUobject  _TLU_print(TLUobject *__PTR args) __NOTHROW;


#endif /* TLU_BUILTIN_H */
