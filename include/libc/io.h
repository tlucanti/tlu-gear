
#ifndef _IO_IO_H_
#define _IO_IO_H_

#include <libc/io_internal.h>
#include <stdint.h>

typedef struct __file_stream file_stream_t;

extern file_stream_t tlu_stdout;
extern file_stream_t tlu_stderr;
extern file_stream_t tlu_stdin;

int putnum(int64_t x);
int putunum(uint64_t x);
int putnum_to(file_stream_t *stream, int64_t x);
int putunum_to(file_stream_t *stream, uint64_t x);

void print_flush(void);
void print_flush_to(file_stream_t *stream);

#endif /* _IO_IO_H_ */

