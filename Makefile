
include .config

BUILD = build
CFLAGS =
LDFLAGS =
CFLAGS += -I include

include cflags.mk

CFLAGS += -D CONFIG_DEBUG=$(CONFIG_DEBUG)
CFLAGS += -D CONFIG_COLOR_OUTPUT=$(CONFIG_COLOR_OUTPUT)
CFLAGS += -D CONFIG_CONTAINER_ALLOC_FAIL=$(CONFIG_CONTAINER_ALLOC_FAIL)

#ifeq ($(CONFIG_SANITIZE),1)
CFLAGS += -fsanitize=address
CFLAGS += -fsanitize=pointer-compare
CFLAGS += -fsanitize=pointer-subtract
CFLAGS += -fsanitize=undefined
CFLAGS += -fsanitize-address-use-after-scope
#CFLAGS += -lasan
CFLAGS += -static-libasan
#endif

#ifeq ($(CONFIG_COVERAGE),1)
CFLAGS += -fprofile-arcs
CFLAGS += -ftest-coverage
LDFLAGS += -lgcov --coverage
#endif

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


include core/Makefile
include utest/Makefile
include bench/Makefile

include libc/$(CONFIG_LIBC_TYPE)/syscall/Makefile
include libc/$(CONFIG_LIBC_TYPE)/mem/Makefile
include libc/$(CONFIG_LIBC_TYPE)/char/Makefile
include libc/$(CONFIG_LIBC_TYPE)/string/Makefile
include libc/$(CONFIG_LIBC_TYPE)/lexical/Makefile
include libc/$(CONFIG_LIBC_TYPE)/io/Makefile

include libc/test/mem/Makefile
include libc/test/string/Makefile
include libc/test/char/Makefile
include libc/test/lexical/Makefile
include libc/test/io/Makefile
include libc/perf/Makefile

include container/cstring/Makefile
include container/cvector/Makefile

include container/cstring/test/Makefile
include container/cvector/test/Makefile

build_all: $(BUILD) $(targets)
	echo $(MESSAGE)
.PHONY: build_all

clean_all:
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
