
#include <unistd.h>
#include <sys/syscall.h>

static inline size_t tlu_write(int fd, const void *buf, size_t size)
{
	return syscall(SYS_write, fd, buf, size);
}

