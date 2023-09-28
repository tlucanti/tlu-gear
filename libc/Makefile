
ROOT = ..
BUILD_DIR = $(ROOT)/build

include $(ROOT)/.config

LIBC_FUNCS = bzero isdigit

LIBC_OBJ = $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(LIBC_FUNCS)))
LIBC_SRC = $(shell ./find_src.sh $(LIBC_FUNCS))

all: $(BUILD_DIR)/libc.a

$(BUILD_DIR)/%.o: generic-fast/%.c
	echo compiling $< to $@
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: generic-slow/%.c
	echo compiling $< to $@
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/libc.a: $(LIBC_OBJ)

