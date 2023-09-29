
#ifndef TLU_NUM_H
# define TLU_NUM_H

# include <TLUdefs.h>
# include <TLUobject.h>

typedef struct  _TLUnum_t
{
    intmax_t     number;
}   _TLUnum;

__WUR TLUobject   _TLU_num_copy(TLUobject _obj);
__WUR intmax_t   _TLU_hash_num(TLUobject _obj);
void _TLU_iadd_num2num(TLUobject _self, TLUobject _other);
__WUR TLUobject _TLU_num2str(TLUobject _obj);

#endif
