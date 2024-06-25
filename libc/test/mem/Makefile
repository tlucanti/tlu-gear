
obj-libmem-test		=
obj-libmem-test		+= memset_test.o

deps-libmem-test	= $(target-libmem) $(target-utest)

target-libmem-test	= build/libmem_unittest.elf

$(eval $(call build_executable,\
	$(target-libmem-test),\
	$(obj-libmem-test),\
	$(deps-libmem-test),\
	libc/test/mem,\
))

