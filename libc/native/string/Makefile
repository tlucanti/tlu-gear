
obj-libstring	=
obj-libstring	+=	strcmp.o
obj-libstring	+=	streq.o
obj-libstring	+=	strlen.o

deps-libstring	= $(target-libmem)

target-libstring	= build/libstring.a

$(eval $(call build_library,\
	$(target-libstring),\
	$(obj-libstring),\
	$(deps-libstring),\
	libc/$(CONFIG_LIBC_TYPE)/string,\
))

