
obj-libconsole		=
obj-libconsole		+= printf_console.o

deps-libconsole		=

target-libconsole	= build/libconsole.a

$(eval $(call build_library,\
	$(target-libconsole),\
	$(obj-libconsole),\
	$(deps-libconsole),\
	libc/io,\
))

