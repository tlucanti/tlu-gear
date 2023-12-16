
TARGET = libbench.a
SRC = func_bench.c
FLAGS = -I include/
DEPS =
DIR = bench

LIBBENCH_TARGET = $(BUILD)/libbench.a

$(eval $(call build_library,\
	$(TARGET),\
	$(SRC),\
	$(FLAGS),\
	$(DEPS),\
	$(DIR)\
))

