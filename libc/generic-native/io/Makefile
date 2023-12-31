
obj-libio	=
deps-libio	=
deps-libio	= io_base.o
deps-libio	= print_flush.o
deps-libio	= print_flush_to.o
deps-libio	= putnum.o
deps-libio	= putnum_to.o
deps-libio	= putunum.o
deps-libio	= putunum_to.o

deps-libio	= $(target-libsyscall)

target-libio	= build/libio.a

$(eval $(call build_library,\
	$(target-libio),\
	$(obj-libio),\
	$(deps-libio),\
	io/$(CONFIG_LIBC_TYPE),\
))

