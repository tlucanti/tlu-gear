
#ifndef TLU_STR_H
# define TLU_STR_H

# include <TLUdefs.h>
# include <TLUobject.h>

typedef struct _TLUstr_t {
    size_t size;
    const char *buf;
    intmax_t hash;
} _TLUstr;

__WUR TLUobject   TLUstr(const char *st);
__WUR TLUobject _TLU_str_copy(TLUobject _obj);
void _TLU_del_str(TLUobject _obj);
__WUR intmax_t _TLU_hash_str(TLUobject _obj);
void _TLU_iadd_str2str(TLUobject self, TLUobject other);
__WUR TLUobject _TLU_str2num(TLUobject _obj);

#endif /* TLU_STR_H */
