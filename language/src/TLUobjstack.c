/*
* @Author: tlucanti
* @Date:   2022-03-27 15:15:43
* @Last Modified by:   tlucanti
* @Last Modified time: 2022-03-27 17:50:09
*/

#include "../inc/TLUobjstack.h"

TLUobject   *_TLUobjstack = NULL;
size_t      _TLUobjstack_allocated = 0;
size_t      _TLUobjstack_size = 0;

void
_TLUobjstack_add(TLUtypeid typeid, void *objec)
{
    if (_TLUobjstack_size + 1 == _TLUobjstack_allocated)
    {
        _TLUobjstack_allocated *= TLUgolden_ratio;
        _TLUobjstack = _TLUreallocate(_TLUobjstack, _TLUobjstack_allocated);
    }

    _TLUobjstack[_TLUobjstack_size] = (TLUobject){typeid, objec};
    __alloc_log("stack at %p -> %p\n", _TLUrbjstack + _TLUobjstack_size,
        _TLUobjstack[_TLUobjstack_size]->object);
    ++_TLUobjstack_size;
}

void
_TLUobjstak_clear()
{
    --_TLUobjstack_size;
    TLUobject *stack_ptr = _TLUobjstack + _TLUobjstack_size;
    __alloc_log("stack: %p\n", stack_ptr);
    while (stack_ptr->typeid != _TLUOBJ_END_TYPEID)
    {
         del(stack_ptr);
         --_TLUobjstack_size;
         --stack_ptr;
    }
    size_t reallocated_size_maybe = _TLUobjstack_allocated / TLUgolden_ratio / TLUgolden_ratio;
    if (_TLUobjstack_allocated > 162 && reallocated_size_maybe > _TLUobjstack_size)
    {
        _TLUobjstack = _TLUreallocate(_TLUobjstack, reallocated_size_maybe);
        _TLUobjstack_size = reallocated_size_maybe;
    }
}
