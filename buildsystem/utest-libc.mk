
TARGET = utest_libc.elf
SRC = libc_test_utils.c libc_test.c
FLAGS = -I include/
DEPS = $(LIBUTEST_TARGET) $(LIBC_TARGET) $(LIBCORE_TARGET)
DIR = libc/test

$(eval $(call build_executable,\
	$(TARGET),\
	$(SRC),\
	$(FLAGS),\
	$(DEPS),\
	$(DIR)\
))

