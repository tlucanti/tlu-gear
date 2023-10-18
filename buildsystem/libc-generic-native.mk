
TARGET = libcgn.a
SRC = \
      memzero.c memset.c memcmp.c memeq.c memnchr.c memchr.c \
      \
      isalnum.c isalpha.c isdigit.c ishex.c islower.c isupper.c \
      isprint.c ispunct.c isspace.c tolower.c toupper.c
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

