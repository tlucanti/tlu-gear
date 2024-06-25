
#ifndef _CORE_MATH_H_
#define _CORE_MATH_H_

#define __cmp_once(x, y, op)            \
	({                              \
		__typeof(x) __x = x;    \
		__typeof(y) __y = y;    \
		__x op __y ? __x : __y; \
	})

#define max(x, y) __cmp_once(x, y, >)
#define min(x, y) __cmp_once(x, y, <)

#define sign(x)                                   \
	({                                        \
		__typeof(x) __x = x;              \
		__x > 0 ? 1 : (__x < 0 ? -1 : 0); \
	})

#endif /* _CORE_MATH_H_ */

