
TARGET = utest_libc_generic_native.elf
SRC = test.c
FLAGS = -I include/
DEPS = $(LIBUTEST_TARGET) $(LIBC_GENERIC_NATIVE_TARGET)
DIR = libc/test

$(eval $(call build_executable,\
	$(TARGET),\
	$(SRC),\
	$(FLAGS),\
	$(DEPS),\
	$(DIR)\
))

