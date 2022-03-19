/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   language.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:56:58 by tlucanti          #+#    #+#             */
/*   Updated: 2022/03/19 23:56:50 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __L_h
# define __L_h

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifdef __ALLOC_DEBUG
#  define __alloc_printf printf
# else
#  define __alloc_printf(...)
# endif /* __ALLOC_DEBUG */

# define _TLUmemcpy memcpy
# define _TLUstrlen strlen
# define _TLUwrite(st) write(1, st, strlen(st))
# define __GLUE2(x, y) x##y
# define __GLUE3(x, y, z) x##y##z

# define _TLUOBJ_SIZE    sizeof(TLUobject)

# define TLUreturn _TLUobjstack_clear(); return
# define _TLUobjstack_add(typeid, objec) *_TLUobjstack = (TLUobject){typeid, objec}; __alloc_printf("stack at %p -> %p\n", _TLUobjstack, _TLUobjstack->object);
# define TLUfun_begin *_TLUobjstack++ = (TLUobject){ _TLUOBJ_END_TYPEID, NULL };


typedef enum _TLUtypeid
{
    _TLUOBJ_END_TYPEID,
    TLUOBJ_NUM_TYPEID,
    TLUOBJ_STR_TYPEID,
    TLU_OBJ_CNT
} TLUtypeid;

typedef struct  _TLUobject_t
{
    TLUtypeid   typeid;
    void        *object;
}   TLUobject;

typedef struct  _TLUnum_t
{
    int     number;
}   _TLUnum;

typedef struct	_TLUstr_t
{
	size_t		size;
	const char	*buf;
	size_t		hash;
}	_TLUstr;

const char *TLUtypenames[] =
{
    [_TLUOBJ_END_TYPEID]    = "<internal type 'END'>",
    [TLUOBJ_NUM_TYPEID]     = "'num'",
    [TLUOBJ_STR_TYPEID]		= "'str'"
};


# define _TLU_add_operator_macro(func, ...) ({ \
	TLUobject __GLUE3(__TLU_, func, internal_macro_args[]) = \
        {__VA_ARGS__, {_TLUOBJ_END_TYPEID, NULL}}; \
    __GLUE2(_TLU_, func)(__GLUE3(__TLU_, func, internal_macro_args)); \
})

# define sum(...) _TLU_add_operator_macro(sum, __VA_ARGS__);
# define print(...) _TLU_add_operator_macro(print, __VA_ARGS__);
// # define iadd(...) _TLU_add_operator_macro(iadd, __VA_ARGS__);


# define del(obj) _TLU_operator_del_vec[(obj).typeid](obj); _TLUdeallocator((obj).object)
# define _TLU_hash_str(...) 0

void _TLU_iadd_error(TLUobject self, TLUobject other);
void _TLU_iadd_num_num(TLUobject self, TLUobject other);
void _TLU_iadd_str_str(TLUobject self, TLUobject other);
void _TLU_del_empty(__attribute__((unused)) TLUobject obj);
void _TLU_del_str(TLUobject obj);
TLUobject _TLU_str_int(TLUobject obj);
TLUobject _TLU_str_self(TLUobject self);

void    TLUinit(); /* should be replaced with macro */
void    TLUstop(); /* should be replaced with macro */
void    _TLUobjstack_clear();
TLUobject   _TLU_sum(TLUobject *args);
TLUobject   intsum(TLUobject a, TLUobject b);
TLUobject   num(int a);
TLUobject   str(const char *st);
TLUobject _TLUstr_size(const char *st, size_t size);

void *_TLUallocator(size_t);
void _TLUdeallocator(void *);

#endif
