
#ifndef TLU_ASSERT_H
# define TLU_ASSERT_H

#include <assert.h>

# ifdef __NO_ASSERT
#  define _TLUassert
# endif /* __NO_ASSERT */
#  define _TLUassert assert
# endif /* __NO_ASSERT */

#endif /* TLU_ASSERT_ */