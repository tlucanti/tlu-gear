
all:
	gcc \
		-Wall -Wextra -c \
		-fdiagnostics-color=always \
		-I ../include \
		utest.c \
		-o ../build/utest.o
	ar rcs \
		../build/libutest.a ../build/utest.o
