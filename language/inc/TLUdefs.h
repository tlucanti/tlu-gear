
#ifndef TLU_DEFS_H
# define TLU_DEFS_H

# include <sys/types.h>
# include <stddef.h>
# include <stdint.h>
# include <limits.h>

# ifndef __COMMON_TLUDEFS
#  define __COMMON_TLUDEFS
#  define __NOTHROW  __attribute__((nothrow))
#  define __WUR      __attribute__((warn_unused_result))
#  define __UNUSED   __attribute__((unused))
#  define __PTR      __restrict
# endif /* __COMMON_TLUDEFS */

# define _GET_NUM(_obj) (_TLUnum *)((_obj).object)
# define _GET_STR(_obj) (_TLUstr *)((_obj).object)

# define _GET_NUM_NUM(_obj) (_GET_NUM(_obj))->number
# define _GET_STR_BUF(_obj) (_GET_STR(_obj))->buf

# define TLUgolden_ratio = 1.6180339887498948482

# define __GLUE2(x, y) x##y
# define __GLUE3(x, y, z) x##y##z

# define __TLU_call_operator_macro(func, ...) ({ \
    TLUobject __internal_macro_argv[] = \
        {__VA_ARGS__, {_TLUOBJ_END_TYPEID, NULL}}; \
    size_t __internal_macro_argc = \
        sizeof(__internal_macro_argv) / sizeof(__internal_macro_argv[0]); \
    __GLUE2(_TLU_, func)(__internal_macro_argc - 1, __internal_macro_argv); \
})

# define __TLU_add_unary_operator_macro(ret_type, func) \
inline ret_type func (TLUobject obj) \
{ \
    return __GLUE3(_TLU_operator_, func, _vec) \
        [obj.typeid](obj); \
}

# define __TLU_add_binary_operator_macro(ret_type, func) \
inline ret_type func (TLUobject self, TLUobject other) \
{ \
    return __GLUE3(_TLU_operator_, func, _vec) \
        [self.typeid][other.typeid](self, other); \
}

# define _TLUinit_macro do { \
    _TLUobjstack = _TLUallocator(sizeof(TLUobject) * 162); \
    _TLUobjstack_allocated = 162; \
    TLUfun_begin; \
} while (0)

# define _TLUstop_macro  do { \
    _TLUobjstack_clear(); \
    _TLUdeallocator(_TLUobjstack); \
} while (0)

#endif /* TLU_DEFS_H */
