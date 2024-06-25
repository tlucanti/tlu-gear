
obj-libmem	=
obj-libmem	+= memset.o

deps-libmem	=

target-libmem	= build/libmem.a

$(eval $(call build_library,\
	$(target-libmem),\
	$(obj-libmem),\
	$(deps-libmem),\
	libc/$(CONFIG_LIBC_TYPE)/mem,\
))

