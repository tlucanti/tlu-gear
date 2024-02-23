
#ifndef _IO_INTERNAL_H_
#define _IO_INTERNAL_H_

#include <core/compiler.h>

#define FILE_BUFFER_SIZE 4096 - sizeof(unsigned long) - sizeof(unsigned long)

struct __file_stream {
	unsigned int offset;
	int fd;
	char buffer[FILE_BUFFER_SIZE];
} __aligned(4096);

#endif /* _IO_INTERNAL_H_ */

