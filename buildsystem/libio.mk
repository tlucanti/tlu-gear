
TARGET = libio.a
SRC = \
	io_base.c \
	putnum.c putunum.c putnum_to.c putunum_to.c \
	print_flush.c print_flush_to.c
FLAGS = -I include/
DEPS = $(LIBC_TARGET) $(LIBSYSCALL_TARGET)
DIR = libc/$(TYPE)/io

LIBIO_TARGET = $(BUILD)/libio.a

$(eval $(call build_library,\
	$(TARGET),\
	$(SRC),\
	$(FLAGS),\
	$(DEPS),\
	$(DIR)\
))

