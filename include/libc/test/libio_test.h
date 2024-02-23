
#ifndef _LIBC_TEST_LIBIO_TEST_H_
#define _LIBC_TEST_LIBIO_TEST_H_

#include <libc/io.h>

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

enum io_func {
	FUNC_PRINT_USHORT,
	FUNC_PRINT_SHORT,
	FUNC_PRINT_UINT,
	FUNC_PRINT_INT,
	FUNC_PRINT_ULONG,
	FUNC_PRINT_LONG,

	FUNC_PRINT_CHAR,
	FUNC_PRINT_STR,
};

struct io_context {
	enum io_func function;
	const char *name;
	int state;

	int io_printed;
	int libc_printed;
	unsigned long generated;
	const char *generated_str;

	file_stream_t io_stream;
	FILE *libc_stream;
};

void utest_io_case(unsigned long val, struct io_context *context);
void utest_io_str(const char *s, struct io_context *context);
void utest_io_suite(unsigned long nr_iter, struct io_context *context);

#endif /* _LIBC_TEST_LIBIO_TEST_H_ */

