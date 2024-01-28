
obj-cstring-container	=
obj-cstring-container	+= cstring.o

deps-cstring-container	= $(target-libmem) $(target-libstring)

target-cstring-container	= build/cstring-container.a

$(eval $(call build_library,\
	$(target-cstring-container),\
	$(obj-cstring-container),\
	$(deps-cstring-container),\
	container/cstring,\
))

