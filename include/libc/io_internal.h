
#ifndef _IO_INTERNAL_H_
#define _IO_INTERNAL_H_

#include <core/compiler.h>

#include <stddef.h>

#define FILE_BUFFER_SIZE 4096 - sizeof(size_t) - sizeof(int)

struct __file_stream {
	char buffer[FILE_BUFFER_SIZE];
	size_t offset;
	int fd;
} __aligned(4096);

#endif /* _IO_INTERNAL_H_ */

