
#ifndef TLU_DEFS_H
# define TLU_DEFS_H

# include <sys/types.h>
# include <stddef.h>
# include <stdint.h>
# include <limits.h>

# ifndef __COMMON_TLUDEFS
#  define __COMMON_TLUDEFS
//#  define __NOTHROW   __attribute__((nothrow)) actually functions can throw exceptions, so I should not use this
#  define __WUR         __attribute__((warn_unused_result))
#  define __UNUSED      __attribute__((unused))
#  define __PTR         __restrict
#  define __ALLOCATOR   __attribute__((malloc))
# endif /* __COMMON_TLUDEFS */

# define __GET_NUM(_obj) (_TLUnum *)((_obj).object)
# define __GET_STR(_obj) (_TLUstr *)((_obj).object)
# define __GET_EXC(_obj) (_TLUexc *)((_obj).object)

# define __GET_NUM_NUM(_obj)     _GET_NUM(_obj)->number
# define __GET_STR_BUF(_obj)     _GET_STR(_obj)->buf
# define __GET_EXC_TYPE(_obj)    _GET_EXC(_obj)->type

# define TLUgolden_ratio    1.6180339887498948482
# define __TLU_END_OBJECT    ((TLUobject){_TLUOBJ_END_TYPEID, NULL})

# define __GLUE2(x, y) x##y
# define __GLUE3(x, y, z) x##y##z

# define __TLU_call_builtin_macro(func, ...) ({ \
    TLUobject __internal_macro_argv[] = \
        {__VA_ARGS__, _TLU_END_OBJECT}; \
    size_t __internal_macro_argc = \
        sizeof(__internal_macro_argv) / sizeof(__internal_macro_argv[0]); \
    __GLUE2(_TLU_, func)(__internal_macro_argc - 1, __internal_macro_argv); \
})

# define __TLU_add_unary_builtin_macro(ret_type, func) \
inline ret_type func (TLUobject obj) \
{ \
    return __GLUE3(_TLU_operator_, func, _vec) \
        [obj.typeid](obj); \
}

# define __TLU_add_binary_builtin_macro(ret_type, func) \
inline ret_type func (TLUobject self, TLUobject other) \
{ \
    return __GLUE3(_TLU_operator_, func, _vec) \
        [self.typeid][other.typeid](self, other); \
}

# define __TLUinit_macro \
    _TLUobjstack = _TLUallocator(sizeof(TLUobject) * 162); \
    _TLUobjstack_allocated = 162; \
    TLUfun_begin; \
    try {

# define __TLUstop_macro \
    if (__global_catch_result) \
        _TLU_exception_traceback(__exception_object); \
    _TLUobjstack_clear(); \
    _TLUdeallocator(_TLUobjstack)

# define __TLUreturn_macro(__retval) return ({ \
    if (__inside_try_block) \
        _TLUmemcpy(__TLU_jmp_buf, __prev_jmp_buf, sizeof(jmp_buf));
    TLUobject __retval_var = __retval; \
    TLUobject __retval_cpy = _TLU_operator_copy_vec[(__retval_var).typeid](__retval_var); \
    TLUscope_end; \
    __retval_cpy; \
})

# define __ASSERT_TYPE_MACRO(_obj, _type, _pred) do { \
    if (_pred) \
        throw(TypeError(format(TLUstr("Expected '" _type "' type, got {}"), TLUstr(TLUtypenames[(_obj).typeid])))); \
} while(0)

# define __TLU_try_block { \
    int __inside_try_block = 1;
    jmp_buf __prev_jmp_buf; \
    _TLUmemcpy(__prev_jmp_buf, __TLU_jmp_buf, sizeof(jmp_buf)); \
    int __global_catch_result = 0;
    if (!setjmp(__TLU_jmp_buf)) {

# define __TLU_except_block(__VA_ARGS__) } if (({ \
    TLUobject __internal_exception_list[] = \
        {__VA_ARGS__, _TLU_END_OBJECT}; \
    TLUobject __internal_exception_list_ptr = \
        (TLUobject *)__internal_exception_list; \
    int __internal_catch_result = 0; \
    while (__internal_exception_list_ptr->typeid != _TLUOBJ_END_TYPEID && \
            !__internal_catch_result) \
    { \
        if (IS_EXC(__internal_exception_list_ptr)) \
            __internal_catch_result |= _GET_EXC_TYPE(__exception_object) & \
                _GET_EXC_TYPE(*__internal_exception_list_ptr); \
        else \
            __internal_catch_result |= __exception_object.typeid == \
                __internal_exception_list_ptr->typeid; \
        __global_catch_reqsult |= __internal_catch_result; \
        ++__internal_exception_list_ptr; \
    } \
    __internal_catch_result; })) {

# define __TLU_except_as(__name) TLUobject __name = __exception_object;

# define __TLU_finally_block } {

# define __TLU_endtry } do { \
    _TLUmemcpy(__TLU_jmp_buf, __prev_jmp_buf, sizeof(jmp_buf));
    if (!__global_catch_result) \
        longjmp(__prev_jmp_buf); \
} while (0)

# define __TLU_endtry_outscope }

# define __TLU_throw_exception(__exc)

#endif /* TLU_DEFS_H */
