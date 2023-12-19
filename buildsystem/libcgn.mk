
TARGET = libcgn.a
MEM_SRC = \
	memzero.c memset.c memcmp.c memeq.c memnchr.c memchr.c memcpy.c \
	memmove.c
STR_SRC = \
	strlen.c strcmp.c streq.c strchr.c strrchr.c sstartswith.c
CHAR_SRC = \
	isalnum.c isalpha.c isdigit.c ishex.c islower.c isupper.c \
	isprint.c ispunct.c isspace.c tolower.c toupper.c
LEXICAL_SRC = \
	numtos.c unumtos.c numtos_base.c unumtos_base.c

SRC = $(addprefix mem/,$(MEM_SRC)) \
      $(addprefix string/,$(STR_SRC)) \
      $(addprefix char/,$(CHAR_SRC)) \
      $(addprefix lexical/,$(LEXICAL_SRC))

FLAGS = -I include/
DEPS =
DIR = libc/generic-native

LIBC_TARGET = $(BUILD)/libcgn.a

$(eval $(call build_library,\
	$(TARGET),\
	$(SRC),\
	$(FLAGS),\
	$(DEPS),\
	$(DIR)\
))

