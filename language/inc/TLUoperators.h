#ifndef TLU_OPERATORS_H
# define TLU_OPERATORS_H

# include <TLUobject.h>
# include <TLUtypeid.h>

extern void (*_TLU_operator_del_vec[TLU_OBJ_CNT])(TLUobject obj);
extern void (*_TLU_operator_iadd_vec[TLU_OBJ_CNT][TLU_OBJ_CNT])(TLUobject, TLUobject);
extern TLUobject (*_TLU_operator_str_vec[TLU_OBJ_CNT])(TLUobject obj);
extern TLUobject (*_TLU_operator_copy_vec[TLU_OBJ_CNT])(TLUobject obj);

void _TLU_iadd_error(TLUobject self, TLUobject other);

#endif
