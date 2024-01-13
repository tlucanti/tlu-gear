
#include <libc/io_internal.h>
#include <unistd.h>

struct __file_stream tlu_stdin = { .offset = 0, .fd = STDIN_FILENO };
struct __file_stream tlu_stdout = { .offset = 0, .fd = STDOUT_FILENO };
struct __file_stream tlu_stderr = { .offset = 0, .fd = STDERR_FILENO };

