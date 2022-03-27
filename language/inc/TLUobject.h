
#ifndef TLU_OBJECT_H
# define TLU_OBJECT_H

# include "TLUtypeid.h"

typedef struct  _TLUobject_t
{
    TLUtypeid   typeid;
    void        *object;
}   TLUobject;

#endif /* TLU_OBJECT_H */
