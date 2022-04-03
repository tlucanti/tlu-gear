
#ifndef TLU_BUILTIN_H
# define TLU_BUILTIN_H

# include <TLUdefs.h>
# include <TLUobjstack.h>
# include <TLUmemory.h>
# include <TLUoperators.h>

# define TLUinit _TLUinit_macro
# define TLUstop _TLUstop_macro
# define TLUfun_begin TLUscope_begin
# define TLUreturn(__retval) _TLUreturn_macro(__retval)

# define try            __TLU_try_block
# define except(...)    __TLU_except_block(__VA_ARGS__)
# define as(__name)     __TLU_except_as(__name)
# define finally        __TLU_finally_block
# define endtry         __TLU_endtry __TLU_endtry_outscope
# define throw(__exc)   __TLU_throw_exception(__exc)

TLUobject   TLUnum(intmax_t a);
TLUobject   TLUstr(const char *st);

TLUobject   TypeError(TLUobject what);
TLUobject   ValueError(TLUobject what);

inline void sum() {}
inline void print() {}
inline void del() {}
inline void num() {}
inline void format() {}

# define sum(...) __TLU_call_builtin_macro(sum, __VA_ARGS__)
# define print(...) __TLU_call_builtin_macro(print, __VA_ARGS__)
# define del(...) __TLU_call_builtin_macro(true_del, __VA_ARGS__)
# define num(...) __TLU_call_builtin_macro(num, __VA_ARGS__)
# define format(...) __TLU_call_builtin_macro(format, __VA_ARGS__)

__TLU_add_unary_builtin_macro(TLUobject, copy)
__TLU_add_unary_builtin_macro(TLUobject, str)

__TLU_add_binary_builtin_macro(void, iadd)

TLUobject   _TLU_num(size_t argc, TLUobject *__PTR argv);
TLUobject   _TLU_str(size_t argc, TLUobject *__PTR argv);

TLUobject   _TLU_sum(size_t argc, TLUobject *__PTR argv);
TLUobject   _TLU_print(size_t argc, TLUobject *__PTR argv);
TLUobject   _TLU_format(size_t argc, TLUobject *__PTR argv);

#endif /* TLU_BUILTIN_H */
