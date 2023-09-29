
#ifndef _CORE_PANIC_
#define _CORE_PANIC_

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include <core/compiler.h>

#ifndef DEBUG
#define __panic(...) abort()
#define __bug(...) /* empty */
#else
#define __panic_reason(name, reason) \
	__panic_impl(name, __FILE__, __LINE__, reason)
#define __panic_pure(name) __panic_impl(name, __FILE__, __LINE__, NULL)
#define ___panic_switch(a1, a2, a3, ...) a3
#define __panic_switch(...) \
	___panic_switch(__VA_ARGS__, __panic_reason, __panic_pure)
#define __panic(name, ...) __panic_switch(__VA_ARGS__)(name, __VA_ARGS__)
#define __bug(...) __panic("BUG", __VA_ARGS__)
#endif

/**
 * usage:
 *  panic() - to abort program
 *  panic("message") to abort program and print reason
 */
#define panic(...) __panic("panic", __VA_ARGS__)

/**
 * usage:
 *  panic() - to abort program
 *  panic("message") to abort program and print reason
 */
#define panic_on(expr, ...)                 \
	do {                                \
		if (unlikely(expr)) {       \
			panic(__VA_ARGS__); \
		}                           \
	} while (false)

#define BUG(...) __bug(__VA_ARGS__)

#define BUG_ON(expr, ...)                   \
	do {                                \
		if (unlikely(expr)) {       \
			__bug(__VA_ARGS__); \
		}                           \
	} while (false)

void __panic_impl(const char *name, const char *file, unsigned long line);

#endif /* _CORE_PANIC_ */
