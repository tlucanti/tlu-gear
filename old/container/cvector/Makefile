
obj-cvector-container	=
obj-cvector-container	+= cvector.o

deps-cvector-container	= $(target-libcore) $(target-utest) $(target-libmem)

target-cvector-container	= build/cvector-container.a

$(eval $(call build_library,\
	$(target-cvector-container),\
	$(obj-cvector-container),\
	$(deps-cvector-container),\
	container/cvector,\
))

