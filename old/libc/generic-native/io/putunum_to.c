
#include <libc/io.h>
#include <libc/lexical.h>
#include <core/compiler.h>

unsigned int putunum_to(file_stream_t *stream, uint64_t x)
{
	unsigned int ret;
	if (unlikely(stream->offset + MAX_NUMBER_LEN >= FILE_BUFFER_SIZE)) {
		print_flush_to(stream);
	}

	ret = unumtos(stream->buffer + stream->offset, x);
	stream->offset += ret;
	return ret;
}

