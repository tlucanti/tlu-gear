
TARGET = libcore.a
SRC = panic.c
FLAGS = -I include/
DEPS =
DIR = core

LIBCORE_TARGET = $(BUILD)/libcore.a

$(eval $(call build_library,\
	$(TARGET),\
	$(SRC),\
	$(FLAGS),\
	$(DEPS),\
	$(DIR)\
))

