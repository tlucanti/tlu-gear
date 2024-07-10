
obj-libcvector	= cvector.o

deps-libcvector	= $(target-libmem) $(target-libconsole)

target-libcvector	= build/libcvector.a

$(eval $(call build_library,\
	$(target-libcvector),\
	$(obj-libcvector),\
	$(deps-libcvector),\
	container/cvector,\
))

