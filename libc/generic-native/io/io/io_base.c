
#include <libc/io_internal.h>

struct __file_stream tlu_stdin = { .offset = 0, .fd = 0 };
struct __file_stream tlu_stdout = { .offset = 0, .fd = 1 };
struct __file_stream tlu_stderr = { .offset = 0, .fd = 2 };

