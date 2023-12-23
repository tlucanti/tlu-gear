
TARGET = libsyscall.a
SRC = syscall.c
FLAGS = -I include/
DEPS =
DIR = libc/$(TYPE)/syscall

LIBSYSCALL_TARGET = $(BUILD)/libsyscall.a

$(eval $(call build_library,\
	$(TARGET),\
	$(SRC),\
	$(FLAGS),\
	$(DEPS),\
	$(DIR)\
))

