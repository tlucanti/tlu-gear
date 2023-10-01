
_generic_slow:
	$(MAKE) -C ../generic-slow
	gcc \
		-Wall -Wextra \
		-fdiagnostics-color=always \
		-I../../include/ \
		test.c \
		-o ../../build/generic_slow_utest.elf \
		-L ../../build \
		-lgeneric-slow -lutest

