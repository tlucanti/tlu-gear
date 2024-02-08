
obj-libstring	=
obj-libstring	+= sstartswith.o
obj-libstring	+= sendswith.o
obj-libstring	+= strchr.o
obj-libstring	+= strcmp.o
obj-libstring	+= streq.o
obj-libstring	+= strlen.o
obj-libstring	+= strrchr.o
obj-libstring	+= strstr.o

deps-libstring	=

target-libstring= build/libstring.a

$(eval $(call build_library,\
	$(target-libstring),\
	$(obj-libstring),\
	$(deps-libstring),\
	libc/$(CONFIG_LIBC_TYPE)/string,\
))

