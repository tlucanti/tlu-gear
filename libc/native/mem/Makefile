
obj-libmem	=
obj-libmem	+= memcmp.o
obj-libmem	+= memcnt.o
obj-libmem	+= memset.o
obj-libmem	+= memset_secure.o
obj-libmem	+= memzero.o
obj-libmem	+= memzero_secure.o

deps-libmem	=

target-libmem	= build/libmem.a

$(eval $(call build_library,\
	$(target-libmem),\
	$(obj-libmem),\
	$(deps-libmem),\
	libc/$(CONFIG_LIBC_TYPE)/mem,\
))

