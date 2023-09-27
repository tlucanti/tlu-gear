
ROOT = ../
BUILD_DIR = $(ROOT)/build

include $(ROOT)/.config

LIBC_FUNCS = bzero isdigit

LIBC_OBJ = $(addprefix build/,$(addsuffix .o,$(LIBC_FUNCS)))
#LIBC_SRC = $(shell find_src.sh $(LIBC_FUNCS))
LIBC_SRC = $(shell ./find_src.sh $(LIBC_FUNCS))

all: $(BUILD_DIR)/libc.a

$(BUILD_DIR)/libc.a:
	# echo $(TEST)
	echo $(LIBC_SRC)

