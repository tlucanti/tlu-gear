
obj-libmem	=
obj-libmem	+= memset.o
obj-libmem	+= memset_secure.o
obj-libmem	+= memzero.o

deps-libmem	=

target-libmem	= build/libmem.a

$(eval $(call build_library,\
	$(target-libmem),\
	$(obj-libmem),\
	$(deps-libmem),\
	libc/$(CONFIG_LIBC_TYPE)/mem,\
))

