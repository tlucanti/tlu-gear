
obj-libmem-test		=
obj-libmem-test		+= libmem_test.o
obj-libmem-test		+= libmem_test_utils.o
obj-libmem-test		+= ../libc_test_utils.o

deps-libmem-test	= $(target-libmem) $(target-utest)

target-libmem-test	= build/libmem_unittest.elf

$(eval $(call build_executable,\
	$(target-libmem-test),\
	$(obj-libmem-test),\
	$(deps-libmem-test),\
	libc/test/mem,\
))

