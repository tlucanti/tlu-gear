
all: build _libc_utest

build:
	mkdir -p build

_utest:
	$(MAKE) -C utest

_libc:
	$(MAKE) -C libc

_libc_utest:
	gcc \
		-Wall -Wextra \
		-O0 -g3 \
		-fdiagnostics-color=always \
		-I include \
		\
		-D DEBUG \
		\
		core/*.c \
		utest/*.c \
		libc/generic-slow/*.c \
		libc/test/test.c




