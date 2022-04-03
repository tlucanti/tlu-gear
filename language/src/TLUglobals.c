
#include <setjmp.h>

#include <TLUobject.h>
#include <TLUdefs.h>

jmp_buf     __TLU_jmp_buf = {};
int         __inside_try_block = 0;
TLUobject   __exception_object = _TLU_END_OBJECT;
