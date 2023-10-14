
TARGET = libcgn.a
SRC = bzero.c memset.c memcmp.c
FLAGS = -I include/
DEPS =
DIR = libc/generic-native

LIBC_GENERIC_NATIVE_TARGET = $(BUILD)/libcgn.a

$(eval $(call build_library,\
	$(TARGET),\
	$(SRC),\
	$(FLAGS),\
	$(DEPS),\
	$(DIR)\
))

