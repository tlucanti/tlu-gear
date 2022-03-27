
#include "../inc/TLUinstd.h"

size_t _TLUwrite(int fd, void *ptr, size_t size)
{
    return write(fd, ptr, size);
}
