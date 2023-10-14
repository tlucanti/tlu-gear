
TARGET = libutest.a
SRC = utest.c utils.c
FLAGS = -I include/
DEPS =
DIR = utest

LIBUTEST_TARGET = $(BUILD)/libutest.a

$(eval $(call build_library,\
	$(TARGET),\
	$(SRC),\
	$(FLAGS),\
	$(DEPS),\
	$(DIR)\
))

