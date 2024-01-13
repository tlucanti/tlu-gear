
#include <libc/io.h>
#include <libc/lexical.h>
#include <core/compiler.h>

int putunum_to(file_stream_t *stream, uint64_t x)
{
	int ret;
	if (unlikely(stream->offset + MAX_NUMBER_LEN >= FILE_BUFFER_SIZE)) {
		print_flush_to(stream);
	}

	ret = unumtos(stream->buffer + stream->offset, x);
	stream->offset += ret;
	return ret;
}

