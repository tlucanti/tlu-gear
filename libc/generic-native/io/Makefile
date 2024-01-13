
obj-libio	=
obj-libio	+= io_base.o
obj-libio	+= print_flush.o
obj-libio	+= print_flush_to.o
obj-libio	+= putnum.o
obj-libio	+= putnum_to.o
obj-libio	+= putunum.o
obj-libio	+= putunum_to.o

deps-libio	= $(target-libsyscall) $(target-liblexical)

target-libio	= build/libio.a

$(eval $(call build_library,\
	$(target-libio),\
	$(obj-libio),\
	$(deps-libio),\
	libc/$(CONFIG_LIBC_TYPE)/io,\
))

