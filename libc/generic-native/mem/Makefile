
obj-libmem	=
obj-libmem	+= memchr.o
obj-libmem	+= memcmp.o
obj-libmem	+= memcpy.o
obj-libmem	+= memeq.o
obj-libmem	+= memmove.o
obj-libmem	+= memnchr.o
obj-libmem	+= memset.o
obj-libmem	+= memzero.o

deps-libmem	=

target-libmem	= build/libmem.a

$(eval $(call build_library,\
	$(target-libmem),\
	$(obj-libmem),\
	$(deps-libmem),\
	libc/$(CONFIG_LIBC_TYPE)/mem,\
))

