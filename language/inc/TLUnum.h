
#ifndef TLU_NUM_H
# define TLU_NUM_H

# include <TLUdefs.h>
# include <TLUobject.h>

typedef struct  _TLUnum_t
{
    intmax_t     number;
}   _TLUnum;

__WUR TLUobject   _TLU_num_copy(TLUobject _obj);
intmax_t   _TLU_hash_num(TLUobject _obj)

#endif
