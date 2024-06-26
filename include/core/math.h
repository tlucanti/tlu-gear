
#ifndef CORE_MATH_H
#define CORE_MATH_H

#include <core/compiler.h>

#define __cmp_once(x, y, op)            \
	({                              \
		typeof(x) __x = (x);    \
		typeof(y) __y = (y);    \
		__x op __y ? __x : __y; \
	})

#define max(x, y) __cmp_once(x, y, >)
#define min(x, y) __cmp_once(x, y, <)

#define sign(x)                                   \
	({                                        \
		typeof(x) __x = (x);              \
		__x > 0 ? 1 : (__x < 0 ? -1 : 0); \
	})

#define swap(a, b)                   \
	do {                         \
		typeof(a) tmp = (a); \
		(a) = (b);           \
		(b) = (tmp);         \
	} while (0)

#endif /* CORE_MATH_H */

