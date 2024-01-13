
#ifndef _LIBC_TEST_LIBIO_TEST_H_
#define _LIBC_TEST_LIBIO_TEST_H_

#include <libc/io.h>

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

enum io_func {
	FUNC_PUTNUM_TO,
	FUNC_PUTUNUM_TO,
};

struct io_context {
	enum io_func function;
	const char *name;
	int state;

	int io_printed;
	int libc_printed;
	uint64_t generated;

	file_stream_t io_stream;
	FILE *libc_stream;
};

void utest_io_case(uint64_t val, struct io_context *context);
void utest_io_suite(unsigned long nr_iter, struct io_context *context);

#endif /* _LIBC_TEST_LIBIO_TEST_H_ */

