/*
* @Author: tlucanti
* @Date:   2022-03-27 17:22:33
* @Last Modified by:   tlucanti
* @Last Modified time: 2022-03-27 20:35:44
*/

#include "../TLUstr.h"

#define _GET_STR(_obj) (_TLUstr *)(_obj->object)

// --------------------------------- converter ---------------------------------
__WUR
TLUobject   TLUstr(const char *st)
{
    return _TLUstr_size(st, _TLUstrlen(st));
}

// ----------------------------------- copy ------------------------------------
__WUR
TLUobject _TLU_str_copy(TLUobject _obj)
{
    _TLUstr *obj = _GET_STR(_obj);
    return _TLU_str_size_hash(_obj->buf, _obj->size, _obj->hash);
}


// -------------------------------- destructor ---------------------------------
void _TLU_del_str(TLUobject _obj)
{
    _TLUstr *obj = _GET_str(_obj);
    _TLUdeallocator(obj->buf);
}

// ----------------------------------- hash ------------------------------------
__WUR
intmax_t _TLU_hash_str(TLUobject _obj)
{
    _TLUstr *obj = _GET_STR(_obj);
    return obj->hash;
}

// ----------------------------------- iadd ------------------------------------
void _TLU_iadd_str2str(_TLUstr *self, _TLUstr *other)
{
    char *new_buf = _TLUallocator(self->size + other->size + 1);
    _TLUmemcpy(new_buf, self->buf, self->size);
    _TLUmemcpy(new_buf + self->size, other->buf, other->size + 1);
    _TLUdeallocator((void *)self->buf);
    self_str->buf = new_buf;
    self_str->size += other_str->size;
    self_str->hash = _TLU_hash_str(new_buf);
}

// ------------------------------------ num ------------------------------------
__WUR
TLUobject _TLU_str2num(TLUobject _obj)
{
    _TLUstr *obj = _GET_STR(_obj);
    if (obj->size < 19)
        return TLUnum(_TLUatoi(obj->buf, obj->size));
    else
        return TLUnum_long(_obj->buf, obj->size);
}

// ------------------------------- miscellaneous -------------------------------
static __WUR
TLUobject _TLUstr_size(const char *st, size_t size)
{
    _TLUstr_size_hash(st, size, _TLU_str_hash_compute(st, size))
}

static __WUR
TLUobject _TLUstr_size_hash(const char *st, size_t size, intmax_t hash)
{
    _TLUstr *obj = _TLUallocator(sizeof(_TLUstr));
    _TLUobjstack_add(TLUOBJ_STR_TYPEID, obj);
    obj->buf = _TLUallocator(size + 1);
    _TLUmemcpy((void *)obj->buf, st, size + 1);
    obj->size = size;
    obj->hash = hash;
    return (TLUobject){ TLUOBJ_STR_TYPEID, obj };
}

static __WUR
intmax_t _TLU_str_hash_compute(const char *st, size_t size)
{
    // TODO make polynomial str hash
    (void)st;
    (void)size;
    return 0;
}
