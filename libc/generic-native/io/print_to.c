
#include <libc/io.h>

#define _STR(x) #x
#define MAX_NUMBER_LEN (sizeof(_STR(ULONG_MAX)) + 1)

static void check_flush(file_stream_t *stream, unsigned long want_write)
{
	if (unlikely(stream->offset + want_write >= FILE_BUFFER_SIZE)) {
		print_flush_to(stream);
	}
}

unsigned int print_ushort_to(file_stream_t *stream, unsigned int x)
{
	return print_ulong_to(stream, x);
}

unsigned int print_short_to(file_stream_t *stream, int x)
{
	return print_long_to(stream, x);
}

unsigned int print_uint_to(file_stream_t *stream, unsigned int x)
{
	return print_ulong_to(stream, x);
}

unsigned int print_int_to(file_stream_t *stream, int x)
{
	return print_long_to(stream, x);
}

unsigned int print_ulong_to(file_stream_t *stream, unsigned long x)
{
	unsigned int ret;

	check_flush(stream, MAX_NUMBER_LEN);
	ret = unumtos(stream->buffer + stream->offset, x);
	stream->offset += ret;
	return ret;
}

unsigned int print_long_to(file_stream_t *stream, long x)
{
	unsigned int ret;

	check_flush(stream, MAX_NUMBER_LEN);
	ret = numtos(stream->buffer + stream->offset, x);
	stream->offset += ret;
	return ret;
}

unsigned int print_char_to(file_stream_t *stream, char c)
{
	check_flush(stream, 1);
	stream->buffer[stream->offset] = c;
	stream->offset++;
	return 1;
}

unsigned int print_str_to(file_stream_t *stream, const char *s)
{
	return print_nstr_to(stream, s, tlu_strlen(s));
}

unsigned int print_nstr_to(file_stream_t *stream, const char *s, unsigned long n)
{
	if (n >= FILE_BUFFER_SIZE / 2) {
		print_flush_to(stream);
		tlu_write(stream->fd, s, n);
	} else {
		check_flush(stream, n);
		tlu_memcpy(stream->buffer + stream->offset, s, n);
		stream->offset += n;
	}

	return n;
}

