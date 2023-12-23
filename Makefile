
include .config

BS_ROOT = buildsystem
BUILD   = build

CFLAGS  = -fdiagnostics-color=always -g3 -O0
CFLAGS += -D DEBUG
CFLAGS += -Wall -Wextra -Werror
CC = gcc
LD = gcc
AR = ar rcsT

TARGETS =

all: build_all

include $(BS_ROOT)/common.mk
include $(BS_ROOT)/build.mk

include $(BS_ROOT)/libcore.mk
include $(BS_ROOT)/libsyscall.mk
include $(BS_ROOT)/libcgn.mk

include $(BS_ROOT)/libutest.mk
include $(BS_ROOT)/libbench.mk
include $(BS_ROOT)/libio.mk

include $(BS_ROOT)/utest-libc.mk
include $(BS_ROOT)/bench-libc.mk
include $(BS_ROOT)/utest-io.mk

build_all: $(TARGETS)

