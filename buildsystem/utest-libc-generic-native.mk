
TARGET = utest_libc_generic_native.elf
SRC = libc_test_utils.c generic_native_test.c
FLAGS = -I include/
DEPS = $(LIBUTEST_TARGET) $(LIBC_GENERIC_NATIVE_TARGET) $(LIBCORE_TARGET)
DIR = libc/test

$(eval $(call build_executable,\
	$(TARGET),\
	$(SRC),\
	$(FLAGS),\
	$(DEPS),\
	$(DIR)\
))

