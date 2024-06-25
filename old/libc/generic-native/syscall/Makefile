
obj-libsyscall	=
obj-libsyscall	= syscall.o

deps-libsyscall	=

target-libsyscall= build/libsyscall.a

$(eval $(call build_library,\
	$(target-libsyscall),\
	$(obj-libsyscall),\
	$(deps-libsyscall),\
	libc/$(CONFIG_LIBC_TYPE)/syscall,\
))

