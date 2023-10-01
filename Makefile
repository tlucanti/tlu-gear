
all: build _libc_utest

build:
	mkdir -p build

_utest:
	$(MAKE) -C utest

_libc:
	$(MAKE) -C libc

_libc_utest: _utest
	$(MAKE) -C libc/test


