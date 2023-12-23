
#include <libc/syscall.h>
#include <unistd.h>

size_t tlu_write(int fd, const void *buf, size_t size)
{
	return write(fd, buf, size);
}

