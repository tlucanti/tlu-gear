
#include <libc/io.h>
#include <libc/syscalls.h>

void print_flush_to(file_stream_t *stream)
{
	tlu_write(stream->fd, stream->buffer, stream->offset);
	stream->offset = 0;
}

