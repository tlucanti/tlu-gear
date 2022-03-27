

#ifndef TLU_DEFS_H
# define TLU_DEFS_H

# include <stddef.h>

# define __NOTHROW __attribute__((nothrow))
# define __WUR __attribute__((warn_unused_result))
# define __PTR __restrict
# define __UNUSED __attribute__((unused))

#endif /* TLU_DEFS_H */
