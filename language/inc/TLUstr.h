
#ifndef TLU_STR_H
# define TLU_STR_H

# include <TLUdefs.h>
# include <TLUobject.h>

typedef struct _TLUstr_t {
    size_t size;
    const char *buf;
    intmax_t hash;
} _TLUstr;

#endif /* TLU_STR_H */
