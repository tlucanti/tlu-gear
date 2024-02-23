
#ifndef _IO_IO_H_
#define _IO_IO_H_

#include <libc/io_internal.h>
#include <core/variadic.h>

typedef struct __file_stream file_stream_t;

extern file_stream_t tlu_stdout;
extern file_stream_t tlu_stderr;
extern file_stream_t tlu_stdin;

unsigned int print_ushort(unsigned int x);
unsigned int print_short(int x);
unsigned int print_uint(unsigned int x);
unsigned int print_int(int x);
unsigned int print_ulong(unsigned long x);
unsigned int print_long(long x);

unsigned int print_ushort_to(file_stream_t *stream, unsigned int x);
unsigned int print_short_to(file_stream_t *stream, int x);
unsigned int print_uint_to(file_stream_t *stream, unsigned int x);
unsigned int print_int_to(file_stream_t *stream, int x);
unsigned int print_ulong_to(file_stream_t *stream, unsigned long x);
unsigned int print_long_to(file_stream_t *stream, long x);

unsigned int print_char(char c);
unsigned int print_str(const char *s);
unsigned int print_nstr(const char *s, unsigned long n);

unsigned int print_char_to(file_stream_t *stream, char c);
unsigned int print_str_to(file_stream_t *stream, const char *s);
unsigned int print_nstr_to(file_stream_t *stream, const char *s, unsigned long n);

void print_flush(void);
void print_flush_to(file_stream_t *stream);

#define print(...) _Generic(						\
	TYPE_SWITCH(__VA_ARGS__),					\
	TYPE_CASE(unsigned short): print_ushort,			\
	TYPE_CASE(short): print_short,					\
	TYPE_CASE(unsigned int): print_uint,				\
	TYPE_CASE(int): print_int,					\
	TYPE_CASE(unsigned long): print_ulong,				\
	TYPE_CASE(long): print_long,					\
									\
	TYPE_CASE(file_stream_t *, unsigned short): print_ushort_to,	\
	TYPE_CASE(file_stream_t *, short): print_short_to,		\
	TYPE_CASE(file_stream_t *, unsigned int): print_uint_to,	\
	TYPE_CASE(file_stream_t *, int): print_int_to,			\
	TYPE_CASE(file_stream_t *, unsigned long): print_ulong_to,	\
	TYPE_CASE(file_stream_t *, long): print_long_to,		\
									\
	TYPE_CASE(char): print_char,					\
	TYPE_CASE(const char *): print_str,				\
									\
	TYPE_CASE(file_stream_t *, char): print_char_to,		\
	TYPE_CASE(file_stream_t *s, const char *): print_str_to		\
	) (__VA_ARGS__)

#endif /* _IO_IO_H_ */

