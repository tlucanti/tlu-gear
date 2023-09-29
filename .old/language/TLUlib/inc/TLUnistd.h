
#ifndef TLU_UNISTD_H
# define TLU_UNISTD_H

# include <TLUdefs.h>

# warning "remove unistd header"
# /* remove this */ include <unistd.h>

ssize_t _TLUwrite(int fd, const void *__PTR ptr, size_t size);

# define _TLUassert assert

#endif TLU_UNISTD_H
