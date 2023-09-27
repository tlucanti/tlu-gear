/*
* @Author: tlucanti
* @Date:   2022-03-27 17:05:21
* @Last Modified by:   tlucanti
* @Last Modified time: 2022-03-27 20:19:56
*/

#include <TLUdefs.h>
#include <TLUobject.h>
#include <TLUtypeid.h>
#include <TLUoperators.h>

#include <TLUnum.h>
#include <TLUstr.h>

# warning "remove stdio header"
# /* remove this */ include <stdio.h>

TLUobject _TLU_operator_self(TLUobject arg) { return arg; }
void _TLU_operator_empty(__UNUSED TLUobject arg) {}

// ------------------------------------ del ------------------------------------
void (*_TLU_operator_del_vec[TLU_OBJ_CNT])(TLUobject obj) = {
        /* END type */ NULL,
        /* NUM type */ _TLU_operator_empty,
        /* STR type */ _TLU_del_str
};

// ----------------------------------- iadd ------------------------------------
void (*_TLU_operator_iadd_vec[TLU_OBJ_CNT][TLU_OBJ_CNT])(TLUobject, TLUobject) = {
                    /* END type */  /* NUM type */     /* STR type */
    /* END type */ {NULL,           NULL,              NULL             },
    /* NUM type */ {NULL,           _TLU_iadd_num2num, _TLU_iadd_error  },
    /* STR type */ {NULL,           _TLU_iadd_error,   _TLU_iadd_str2str}
};

void _TLU_iadd_error(TLUobject self, TLUobject other)
{
    printf("operator += type error: cannot sum types %s and %s\n",
        TLUtypenames[self.typeid], TLUtypenames[other.typeid]);
}

// ------------------------------------ str ------------------------------------
TLUobject (*_TLU_operator_str_vec[TLU_OBJ_CNT])(TLUobject obj) = {
    /* END type */ NULL,
    /* NUM type */ _TLU_num2str,
    /* STR type */ _TLU_operator_self
};

// ----------------------------------- copy ------------------------------------
TLUobject (*_TLU_operator_copy_vec[TLU_OBJ_CNT])(TLUobject obj) = {
    /* END type */ NULL,
    /* NUM type */ _TLU_num_copy,
    /* STR type */ _TLU_str_copy
};
