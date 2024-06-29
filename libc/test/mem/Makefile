
obj-libmem-test		=
obj-libmem-test		+= memcmp_test.o
obj-libmem-test		+= memset_secure_test.o
obj-libmem-test		+= memset_test.o
obj-libmem-test		+= memzero_secure_test.o
obj-libmem-test		+= memzero_test.o
obj-libmem-test		+= libmem_test.o

deps-libmem-test	= $(target-libmem) $(target-utest)

target-libmem-test	= build/libmem_unittest.elf

$(eval $(call build_executable,\
	$(target-libmem-test),\
	$(obj-libmem-test),\
	$(deps-libmem-test),\
	libc/test/mem,\
))

