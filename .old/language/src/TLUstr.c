/*
* @Author: tlucanti
* @Date:   2022-03-27 17:22:33
* @Last Modified by:   tlucanti
* @Last Modified time: 2022-03-27 20:35:44
*/

#include <TLUstr.h>
#include <TLUstring.h>
#include <TLUmemory.h>
#include <TLUbuiltin.h>

static __WUR TLUobject _TLUstr_size(const char *st, size_t size);
static __WUR TLUobject _TLUstr_size_hash(const char *st, size_t size, intmax_t hash);
static __WUR intmax_t _TLU_str_hash_compute(const char *st, size_t size);

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
    return _TLUstr_size_hash(obj->buf, obj->size, obj->hash);
}


// -------------------------------- destructor ---------------------------------
void _TLU_del_str(TLUobject _obj)
{
    _TLUstr *obj = _GET_STR(_obj);
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
void _TLU_iadd_str2str(TLUobject _self, TLUobject _other)
{
    _TLUstr *self = _GET_STR(_self);
    _TLUstr *other = _GET_STR(_other);
    char *new_buf = _TLUallocator(self->size + other->size + 1);
    _TLUmemcpy(new_buf, self->buf, self->size);
    _TLUmemcpy(new_buf + self->size, other->buf, other->size + 1);
    _TLUdeallocator((void *)self->buf);
    self->buf = new_buf;
    self->size += other->size;
    self->hash = _TLU_str_hash_compute(new_buf, self->size);
}

// ------------------------------- miscellaneous -------------------------------
static __WUR
TLUobject _TLUstr_size(const char *st, size_t size)
{
    _TLUstr_size_hash(st, size, _TLU_str_hash_compute(st, size));
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
