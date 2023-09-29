
#ifndef _CORE_COMPILER_H_
#define _CORE_COMPILER_H_

#ifndef __always_inline
# define __always_inline inline __attribute__((__always_inline__))
#endif

#ifndef noinline
# define noinline __attribute__((__noinline__))
#endif

#ifndef __used
# define __used __attribute__((__used__))
#endif

#ifndef __unused
# define __unused __attribute__((__unused__))
#endif

#ifndef __packed
# define __packed __attribute__((__packed__))
#endif

#ifndef __noret
# define __noret __attribute__((__noreturn__))
#endif

#ifndef __cold
# define __cold __attribute__((__cold__))
#endif

#ifndef likely
# define likely(expr) __builtin_expect(!!(expr), 1)
#endif

#ifndef unlikely
# define unlikely(expr) __builtin_expect(!!(expr), 0)
#endif

#endif /* _CORE_COMPILER_H_ */

