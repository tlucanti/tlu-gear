
#ifndef CORE_RWONCE_H
#define CORE_RWONCE_H

#include <core/compiler.h>

#define READ_ONCE(x) ({ (*(const volatile typeof_unqual(x) *)&(x)); })

#define WRITE_ONCE(x, val)                                  \
	do {                                                \
		*(volatile typeof_unqual(x) *)&(x) = (val); \
	} while (0)

#endif /* CORE_RWONCE_H */

