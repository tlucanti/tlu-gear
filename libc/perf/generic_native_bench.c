
#include <bench/bench.h>
#include <libc/mem.h>

#include <stddef.h>
#include <stdbool.h>

#include <string.h>
#include <malloc.h>

struct context {
	char *memory;
	size_t size;
	bool libc;
};

static void memset_callback(void *vcontext)
{
	struct context *context = vcontext;

	if (context->libc) {
		memset(context->memory, context->size, 0xff);
	} else {
		tlu_memset(context->memory, context->size, 0xff);
	}
}
int main()
{
	struct context context;

	context.size = 10;
	context.memory = malloc(sizeof(char) * 4090);

	context.libc = 0;
	func_bench(memset_callback, &context);
	context.libc = 1;
	func_bench(memset_callback, &context);
}

