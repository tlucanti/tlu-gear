
BUILD = build
CFLAGS = -Wall -Wextra -I include

CC = gcc
LD = gcc
AR = ar rcsT

targets =
obj =

all: build_all
.PHONY: all

clean: clean_all
.PHONY: clean

define build_library

$(eval target = $(strip $1))
$(eval obj = $(strip $2))
$(eval deps = $(strip $3))
$(eval dir = $(strip $4))

$(eval obj = $(addprefix $(dir)/,$(obj)))

$(eval targets = $(targets) $(target))

$(target): $(deps) $(obj)
	@echo AR $(basename $(target))
	@$(AR) $(target) $(obj) $(deps)

endef

include .config

include libc/$(CONFIG_LIBC_TYPE)/Makefile

build_all: $(build) $(targets)
.PHONY: build_all

clean_all:
	@for ob in $(obj); do test -f $$ob && echo "CLEAN $$(basename $$ob)"; $(RM) $$ob; done
.PHONY: clean_all

%.o: %.c
	@echo "CC $$(basename $@)"
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	echo "ASM $@"

$(BUILD):
	mkdir -p $(BUILD)
