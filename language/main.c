/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <tlucanti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:19:56 by tlucanti          #+#    #+#             */
/*   Updated: 2022/03/19 23:56:17 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "language.h"

TLUobject   *_TLUobjstack;

void (*_TLU_operator_iadd_vec[TLU_OBJ_CNT][TLU_OBJ_CNT])(TLUobject self, TLUobject other) = {
                    /* END type */  /* NUM type */     /* STR type */
    /* END type */ {NULL,           NULL,              NULL},
    /* NUM type */ {NULL,           _TLU_iadd_num_num, _TLU_iadd_error},
    /* STR type */ {NULL,           _TLU_iadd_error,   _TLU_iadd_str_str}
};

void _TLU_iadd_error(TLUobject self, TLUobject other)
{
    printf("operator += type error: cannot sum types %s and %s\n",
        TLUtypenames[self.typeid], TLUtypenames[other.typeid]);
}

void _TLU_iadd_num_num(TLUobject self, TLUobject other)
{
    ((_TLUnum *)self.object)->number += ((_TLUnum *)other.object)->number;
}

void _TLU_iadd_str_str(TLUobject self, TLUobject other)
{
    _TLUstr *self_str = (_TLUstr *)self.object;
    _TLUstr *other_str = (_TLUstr *)other.object;

    char *new_buf = _TLUallocator(self_str->size + other_str->size + 1);
    _TLUmemcpy(new_buf, self_str->buf, self_str->size);
    _TLUmemcpy(new_buf + self_str->size, other_str->buf, other_str->size + 1);
    _TLUdeallocator((void *)self_str->buf);
    self_str->buf = new_buf;
    self_str->size += other_str->size;
    self_str->hash = _TLU_hash_str(new_buf);
}

// -----------------------------------------------------------------------------

void (*_TLU_operator_del_vec[TLU_OBJ_CNT])(TLUobject obj) = {
    /* END type */ NULL,
    /* NUM type */ _TLU_del_empty,
    /* STR type */ _TLU_del_str
};

void _TLU_del_empty(__attribute__((unused)) TLUobject obj) {}
void _TLU_del_str(TLUobject obj)
{
    _TLUdeallocator((void *)((_TLUstr *)obj.object)->buf);
}

// -----------------------------------------------------------------------------

TLUobject (*_TLU_operator_str_vec[TLU_OBJ_CNT])(TLUobject obj) = {
    /* END type */ NULL,
    /* NUM type */ _TLU_str_int,
    /* STR type */ _TLU_str_self
};

TLUobject _TLU_str_int(TLUobject obj)
{
    char    buf[20];
    sprintf(buf, "%d", ((_TLUnum *)obj.object)->number);
    return str(buf);
}

TLUobject _TLU_str_self(TLUobject self) { return self; }

// -----------------------------------------------------------------------------

void    TLUinit() /* should be replaced with macro */
{
    _TLUobjstack = _TLUallocator(_TLUOBJ_SIZE * 100);
    TLUfun_begin;
}

void    TLUstop() /* should be replaced with macro */
{
    _TLUobjstack_clear();
	_TLUdeallocator(_TLUobjstack);
}

void    _TLUobjstack_clear()
{
	--_TLUobjstack;
	__alloc_printf("stack: %p\n", _TLUobjstack);
    while (_TLUobjstack->typeid != _TLUOBJ_END_TYPEID)
    {
        del(*_TLUobjstack);
        --_TLUobjstack;
    }
}

TLUobject   _TLU_sum(TLUobject *args)
{
    TLUobject counter = num(0);
    while (args->typeid != _TLUOBJ_END_TYPEID)
    {
        _TLU_operator_iadd_vec[counter.typeid][args->typeid](counter, *args);
        ++args;
    }
    return counter;
}

TLUobject _TLU_print(TLUobject *args)
{
    int cnt = 0;
    if (args->typeid == _TLUOBJ_END_TYPEID)
        return num(_TLUwrite("\n"));
    while (1)
    {
        TLUobject arg_str = _TLU_operator_str_vec[args->typeid](*args);
        cnt += _TLUwrite(((_TLUstr *)arg_str.object)->buf);
        ++args;
        if (args->typeid == _TLUOBJ_END_TYPEID)
            break ;
        cnt += _TLUwrite(" ");
    }
    cnt += _TLUwrite("\n");
    return num(cnt);
}


void   iadd(TLUobject a, TLUobject b)
{
    _TLU_operator_iadd_vec[a.typeid][b.typeid](a, b);
}

TLUobject   intsum(TLUobject a, TLUobject b)
{
    TLUfun_begin;

    TLUreturn sum(a, b);
}

int main()
{
    TLUinit();

    TLUobject   a  = num(123);
    TLUobject   b  = num(456);
    TLUobject   c  = num(789);
    TLUobject   sm = sum(a, b, c);

    print(str("sum of"), a, c, str("and"), b, str("="), sm);

    TLUobject   s1 = str("hello-");
    TLUobject   s2 = str("world");
    TLUobject   ss = str("");
    iadd(ss, s1);
    iadd(ss, s2);

    print(str("sum of"), s1, str("and"), s2, str("is"), ss);

    TLUstop();
}

TLUobject   num(int a)
{
    _TLUnum  *obj = _TLUallocator(sizeof(_TLUnum));
    _TLUobjstack_add(TLUOBJ_NUM_TYPEID, obj);
    obj->number = a;
    return (TLUobject){ TLUOBJ_NUM_TYPEID, obj };
}

TLUobject   str(const char *st)
{
    return _TLUstr_size(st, _TLUstrlen(st));
}

TLUobject _TLUstr_size(const char *st, size_t size)
{
    _TLUstr *obj = _TLUallocator(sizeof(_TLUstr));
    _TLUobjstack_add(TLUOBJ_STR_TYPEID, obj);
    obj->buf = _TLUallocator(size + 1);
    _TLUmemcpy((void *)obj->buf, st, size + 1);
    obj->size = size;
    obj->hash = _TLU_hash_str(st);
    return (TLUobject){ TLUOBJ_STR_TYPEID, obj };
}

void *_TLUallocator(size_t size)
{
	void *ret = malloc(size);
	__alloc_printf("allocated: %p\n", ret);
	return ret;
}

void _TLUdeallocator(void *ptr)
{
	__alloc_printf("deallocating %p\n", ptr);
	free(ptr);
}
