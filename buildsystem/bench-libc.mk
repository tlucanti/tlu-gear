
TARGET = bench_libc.elf
SRC = libc_bench.c
FLAGS = -I include/
DEPS = $(LIBBENCH_TARGET) $(LIBC_TARGET) $(LIBCORE_TARGET)
DIR = libc/perf

$(eval $(call build_executable,\
	$(TARGET),\
	$(SRC),\
	$(FLAGS),\
	$(DEPS),\
	$(DIR)\
))

