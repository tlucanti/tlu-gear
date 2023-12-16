
TARGET = bench_libc_generic_native.elf
SRC = generic_native_bench.c
FLAGS = -I include/
DEPS = $(LIBBENCH_TARGET) $(LIBC_GENERIC_NATIVE_TARGET) $(LIBCORE_TARGET)
DIR = libc/perf

$(eval $(call build_executable,\
	$(TARGET),\
	$(SRC),\
	$(FLAGS),\
	$(DEPS),\
	$(DIR)\
))

