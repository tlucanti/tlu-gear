
#include <TLUnistd.h>

ssize_t _TLUwrite(int fd, const void *__PTR ptr, size_t size)
{
    return write(fd, ptr, size);
}
