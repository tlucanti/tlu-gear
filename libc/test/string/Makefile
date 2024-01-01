
obj-libstring-test	=
obj-libstring-test	+= libstring_test.o
obj-libstring-test	+= libstring_test_utils.o
obj-libstring-test	+= ../libc_test_utils.o
obj-libstring-test	+= ../mem/libmem_test_utils.o

deps-libstring-test	= $(target-libstring) $(target-libmem) $(target-utest)

target-libstring-test	= build/libstring_unittest.elf

$(eval $(call build_executable,\
	$(target-libstring-test),\
	$(obj-libstring-test),\
	$(deps-libstring-test),\
	libc/test/string,\
))

