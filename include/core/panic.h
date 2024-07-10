
#ifndef CORE_PANIC_H
#define CORE_PANIC_H

#include <core/compiler.h>
#include <core/types.h>
#include <core/console.h>

#define tlu_panic(message) __tlu_panic(message, __FILE__, __LINE__)

#if CONFIG_PANIC_SILENT
__cold __noret
static inline void __tlu_panic(const char *message, const char *file, uint line)
{
	while (true);
}

#else
__cold __noret
static inline void __tlu_panic(const char *message, const char *file, uint line)
{
	tlu_console_puts("[PANIC]: ");
	tlu_console_puts(file);
	tlu_console_putc(':');
	tlu_console_putn(line);
	tlu_console_puts(": ");
	tlu_console_puts(message);
	tlu_console_puts("\r\n");
	while (true);
}
#endif

#endif /* CORE_PANIC_H */

