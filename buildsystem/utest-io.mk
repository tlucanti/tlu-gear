
TARGET = utest_io.elf
SRC = io_test.c
FLAGS = -I include/
DEPS = $(LIBUTEST_TARGET) $(LIBIO_TARGET) $(LIBCORE_TARGET)
DIR = libc/test

$(eval $(call build_executable,\
	$(TARGET),\
	$(SRC),\
	$(FLAGS),\
	$(DEPS),\
	$(DIR)\
))

