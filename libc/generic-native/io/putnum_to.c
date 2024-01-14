
#include <libc/io.h>
#include <libc/lexical.h>
#include <core/compiler.h>

unsigned int putnum_to(file_stream_t *stream, int64_t x)
{
	unsigned int ret;

	if (unlikely(stream->offset + MAX_NUMBER_LEN >= FILE_BUFFER_SIZE)) {
		print_flush_to(stream);
	}

	ret = numtos(stream->buffer + stream->offset, x);
	stream->offset += ret;
	return ret;
}

