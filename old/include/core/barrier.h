
#ifndef _CORE_BARRIER_H_
#define _CORE_BARRIER_H_

#define READ_ONCE(x) (*(const volatile typeof_unqual(x) *)&(x))

#define WRITE_ONCE(x, val)                                  \
	do {                                                \
		*(volatile typeof_unqual(x) *)&(x) = (val); \
	} while (false)

#endif /* _CORE_BARRIER_H_ */

