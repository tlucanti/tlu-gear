#!/bin/make

all: valgrind gcov

valgrind:
	@echo BUILDING LIBMEM FOR VALGRIND
	@CONFIG_SILENT=1 make --environment-overrides --quiet clean
	@CONFIG_SILENT=1 make --environment-overrides clean
	@CONFIG_SANITIZE=0 make --environment-overrides --quiet -j
	@echo
	@echo VALGRIND LIBMEM
	@valgrind ./build/libmem_unittest.elf
	@echo
.PHONY: valgrind

gcov:
	@echo BILDING LIBMEM FOR GCOV
	@CONFIG_SILENT=1 make --environment-overrides --quiet clean
	@CONFIG_SANITIZE=0 make --environment-overrides --quiet -j
	@echo
	@./build/libmem_unittest.elf
	@echo
	@for f in $$(ls libc/native/mem/*.c); do \
		printf "GCOV $$(basename $$f):\t"; \
		gcov $$f | tail -n1 | grep -oP "\d+[.]\d+[%]"; \
	done
	@echo
.PHONY: gcov

