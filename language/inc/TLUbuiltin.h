
#ifndef TLU_BUILTIN_H
# define TLU_BUILTIN_H

# include <TLUdefs.h>
# include <TLUobjstack.h>
# include <TLUmemory.h>
# include <TLUoperators.h>

# define TLUinit _TLUinit_macro
# define TLUstop _TLUstop_macro

TLUobject   TLUnum(intmax_t a);
TLUobject   TLUstr(const char *st);

TLUobject   TypeError(TLUobject what);
TLUobject   ValueError(TLUobject what);

inline void sum() {}
inline void print() {}
inline void del() {}
inline void num() {}
inline void format() {}

# define sum(...) __TLU_call_operator_macro(sum, __VA_ARGS__)
# define print(...) __TLU_call_operator_macro(print, __VA_ARGS__)
# define del(...) __TLU_call_operator_macro(del, __VA_ARGS__)
# define num(...) __TLU_call_operator_macro(num, __VA_ARGS__)
# define format(...) __TLU_call_operator_macro(format, __VA_ARGS__)

__TLU_add_binary_operator_macro(void, iadd)

__TLU_add_unary_operator_macro(TLUobject, copy)
__TLU_add_unary_operator_macro(TLUobject, str)

TLUobject   _TLU_sum(size_t argc, TLUobject *__PTR argv) __NOTHROW;
TLUobject   _TLU_print(size_t argc, TLUobject *__PTR argv) __NOTHROW;
TLUobject   _TLU_format(size_t argc, TLUobject *__PTR argv) __NOTHROW;

#endif /* TLU_BUILTIN_H */
