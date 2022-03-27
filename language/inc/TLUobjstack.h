
#ifndef TLU_OBJSTACK_H
# define TLU_OBJSTACK_H

# include "TLUdefs.h"
# include "TLUobject.h"

extern TLUobject   *_TLUobjstack = NULL;
extern size_t      _TLUobjstack_allocated = 0;
extern size_t      _TLUobjstack_size = 0;

void _TLUobjstack_add(TLUtypeid typeid, TLUobject objec) __NOTHROW;
void _TLUobjstack_clear() __NOTHROW;

# define TLUscope_begin do { \
    _TLUobjstack[_TLUobjstack_size++] = (TLUobject){ _TLUOBJ_END_TYPEID, NULL }; \
} while (0)

# define TLUscope_end do { \
    _TLUobjstack_clear(); \
} while (0)

# define TLUfun_begin TLUscope_begin

# define TLUreturn(__retval) do { \
    TLUobject _retval_cpy = _TLUcopy(__reval); \
    TLUscope_end; \
    return _retval_cpy; \
} while (0)

#endif /* TLU_OBJSTACK_H */
