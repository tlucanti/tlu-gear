
obj-libmem-test		=
obj-libmem-test		+= memchr_test.o
obj-libmem-test		+= memccpy_test.o
obj-libmem-test		+= memcmp_test.o
obj-libmem-test		+= memcnt_test.o
obj-libmem-test		+= memcpy_test.o
obj-libmem-test		+= memeq_test.o
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

