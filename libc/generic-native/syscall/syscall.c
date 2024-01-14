
#include <libc/syscall.h>
#include <unistd.h>

int64_t tlu_write(int fd, const void *buf, uint64_t size)
{
	return write(fd, buf, size);
}

