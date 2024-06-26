
include .config

BUILD = build
CFLAGS =
LDFLAGS =
CFLAGS += -I include

include cflags.mk

CFLAGS += -D CONFIG_DEBUG=$(CONFIG_DEBUG)
CFLAGS += -D CONFIG_UTEST_FIRST_FAIL=$(CONFIG_UTEST_FIRST_FAIL)
CFLAGS += -D CONFIG_UTEST_COLOR=$(CONFIG_UTEST_COLOR)

ifeq ($(CONFIG_SANITIZE),1)
CFLAGS += -fsanitize=address
CFLAGS += -fsanitize=pointer-compare
CFLAGS += -fsanitize=pointer-subtract
CFLAGS += -fsanitize=undefined
CFLAGS += -fsanitize-address-use-after-scope
CFLAGS += -static-libasan
endif

ifeq ($(CONFIG_COVERAGE),1)
CFLAGS += -fprofile-arcs
CFLAGS += -ftest-coverage
LDFLAGS += -lgcov --coverage
endif

ifeq ($(CONFIG_DEBUG),1)
CFLAGS += -O0 -g3 -fno-inline
MESSAGE = "build in debug mode"
else
CFLAGS += -O3 -g0
MESSAGE = "build in release mode"
endif

CC = gcc
LD = gcc
AR = ar rcsT
RM = rm -f

targets =
obj-y =

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
$(eval obj-y = $(obj-y) $(obj))

$(target): $(deps) $(obj)
	@echo AR $(basename $(target).a)
	@$(AR) $(target) $(obj) $(deps)

endef

define build_executable

$(eval target = $(strip $1))
$(eval obj = $(strip $2))
$(eval deps = $(strip $3))
$(eval dir = $(strip $4))

$(eval obj = $(addprefix $(dir)/,$(obj)))

$(eval targets = $(targets) $(target))
$(eval obj-y = $(obj-y) $(obj))

$(target): $(deps) $(obj)
	@echo LD $(basename $(target).elf)
	@$(LD) -o $(target) $(obj) $(deps) $(LDFLAGS) $(CFLAGS)

endef


include utest/Makefile

include libc/native/mem/Makefile

include libc/test/mem/Makefile


build_all: $(BUILD) $(targets)
	echo $(MESSAGE)
.PHONY: build_all

clean_all:
	@rm -f $$(find . -name '*.gcno')
	@rm -f $$(find . -name '*.gcda')
	@rm -f $$(find . -name '*.gcov')
	@for ob in $(obj-y) $(targets); do \
		test -f $$ob && echo "CLEAN $$(basename $$ob)"; \
		$(RM) $$ob; \
	done
.PHONY: clean_all

%.o: %.c
	@echo "CC $$(basename $@)"
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	echo "ASM $@"

$(BUILD):
	@mkdir -p $(BUILD)

