
include .config

BS_ROOT = buildsystem
BUILD   = build

CFLAGS = -Wall -Wextra
CC = clang
LD = clang
AR = ar rcs

TARGETS =

all: build_all

include $(BS_ROOT)/common.mk
include $(BS_ROOT)/build.mk

include $(BS_ROOT)/libutest.mk
include $(BS_ROOT)/libc-generic-native.mk

include $(BS_ROOT)/utest-libc-generic-native.mk

build_all: $(BUILD) $(TARGETS)

$(BUILD):
	@echo MK $(BUILD)
	@mkdir -p $(BUILD)

