
#include <libc/test/libc_test_utils.h>
#include <libc/test/libio_test.h>
#include <utest/utest.h>
#include <utest/utils.h>
#include <core/panic.h>

#include <libc/io.h>

#include <limits.h>
#include <inttypes.h>

struct pipe_fd {
	union {
		int pipe[2];
		struct {
			int read;
			int write;
		};
	};
};

static void utest_io_callback(struct io_context *context)
{
	unsigned long num = context->generated;

	switch (context->function) {
	case FUNC_PRINT_USHORT:
		print_ushort_to(&context->io_stream, (unsigned short)num);
		fprintf(context->libc_stream, "%hu", (unsigned short)num);
		break;

	case FUNC_PRINT_SHORT:
		print_short_to(&context->io_stream, (short)num);
		fprintf(context->libc_stream, "%hd", (short)num);
		break;

	case FUNC_PRINT_UINT:
		print_uint_to(&context->io_stream, (unsigned int)num);
		fprintf(context->libc_stream, "%u", (unsigned int)num);
		break;

	case FUNC_PRINT_INT:
		print_int_to(&context->io_stream, (int)num);
		fprintf(context->libc_stream, "%d", (int)num);
		break;

	case FUNC_PRINT_ULONG:
		print_ulong_to(&context->io_stream, (unsigned long)num);
		fprintf(context->libc_stream, "%lu", (unsigned long)num);
		break;

	case FUNC_PRINT_LONG:
		print_long_to(&context->io_stream, (long)num);
		fprintf(context->libc_stream, "%ld", (long)num);
		break;

	case FUNC_PRINT_CHAR:
		print_char_to(&context->io_stream, (char)num);
		fprintf(context->libc_stream, "%c", (char)num);
		break;

	case FUNC_PRINT_STR:
		print_str_to(&context->io_stream, context->generated_str);
		fprintf(context->libc_stream, "%s", context->generated_str);
		break;

	default:
		BUG("utest::io_suite: unknown function");
	}

	fflush(context->libc_stream);
	print_flush_to(&context->io_stream);
}

void utest_io_case(unsigned long val, struct io_context *context)
{
	struct pipe_fd io_pipe;
	struct pipe_fd libc_pipe;
	unsigned char *io_printed, *libc_printed;
	size_t io_nr_printed, libc_nr_printed;

	utest_pipe(io_pipe.pipe);
	utest_pipe(libc_pipe.pipe);

	context->io_stream.offset = 0;
	context->io_stream.fd = io_pipe.write;

	context->libc_stream = fdopen(libc_pipe.write, "w");
	panic_on(context->libc_stream == NULL, "fdopen fail");

	context->generated = val;
	utest_io_callback(context);

	close(io_pipe.write);
	fclose(context->libc_stream);

	io_printed = (unsigned char *)utest_read_all(io_pipe.read, &io_nr_printed);
	libc_printed = (unsigned char *)utest_read_all(libc_pipe.read, &libc_nr_printed);

	ASSERT_ZERO(utest_validate_memory_differ(libc_printed, libc_nr_printed,
						 io_printed, io_nr_printed));

	close(io_pipe.read);
	close(libc_pipe.read);
}

void utest_io_str(const char *s, struct io_context *context)
{
	context->generated_str = s;
	utest_io_case(0, context);
}

void utest_io_suite(unsigned long nr_iter, struct io_context *context)
{
	uint64_t num;
	int ret;

	context->state = 0;
	utest_progress_start();

	for (unsigned long i = 0; i < nr_iter; ) {
		utest_progress(i, nr_iter);

		num = utest_random();

		switch (context->state) {
		case 0:
			num = context->generated % 100;
			ret = NEXT_STATE;
			break;
		case 1:
			num = context->generated % 10000;
			ret = NEXT_STATE;
			break;
		case 2:
			num = context->generated % INT_MAX;
			ret = NEXT_STATE;
			break;
		case 3:
			num = context->generated % 100;
			num = -num;
			ret = NEXT_STATE;
			break;
		case 4:
			num = context->generated % 10000;
			num = -num;
			ret = NEXT_STATE;
			break;
		case 5:
			num = context->generated % INT_MAX;
			num = -num;
			ret = STATE_DONE;
			break;
		default:
			BUG("utest::utest_io_suite: invalid state");
		}

		utest_io_case(num, context);

		switch (ret) {
		case NEXT_STATE:
			context->state++;
			break;
		case STATE_DONE:
			i++;
			context->state = 0;
			break;
		default:
			BUG("utest::utest_io_suite: invalid return state");
		}
	}

	utest_progress_done();
}

