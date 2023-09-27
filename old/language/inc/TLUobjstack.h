
#ifndef TLU_OBJSTACK_H
# define TLU_OBJSTACK_H

# include <TLUdefs.h>
# include <TLUobject.h>
# include <TLUtypeid.h>

extern TLUobject   *_TLUobjstack;
extern size_t      _TLUobjstack_allocated;
extern size_t      _TLUobjstack_size;

void _TLUobjstack_add(TLUtypeid typeid, const void *objec);
void _TLUobjstack_clear();

# define TLUscope_begin do { \
    _TLUobjstack[_TLUobjstack_size++] = _TLU_END_OBJECT; \
} while (0)

# define TLUscope_end do { \
    _TLUobjstack_clear(); \
} while (0)

#endif /* TLU_OBJSTACK_H */
