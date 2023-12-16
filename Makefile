
include .config

BS_ROOT = buildsystem
BUILD   = build

CFLAGS  = -fdiagnostics-color=always -g3 -O0
CFLAGS += -D DEBUG
CFLAGS += -Wall -Wextra -Werror
CC = gcc
LD = gcc
AR = ar rcs

TARGETS =

all: build_all

include $(BS_ROOT)/common.mk
include $(BS_ROOT)/build.mk

include $(BS_ROOT)/libcore.mk
include $(BS_ROOT)/libutest.mk
include $(BS_ROOT)/libbench.mk
include $(BS_ROOT)/libc-generic-native.mk

include $(BS_ROOT)/utest-libc-generic-native.mk
include $(BS_ROOT)/bench-libc-generic-native.mk

build_all: $(TARGETS)

