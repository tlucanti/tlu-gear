
obj-libc-test	=
obj-libc-test	+= libc_test.o
obj-libc-test	+= libc_test_utils.o

deps-libc-test	= $(target-libc) $(target-utest) $(target-core)

target-libc-test= build/libc_unittest.elf

$(eval $(call build_executable,\
	$(target-libc-test),\
	$(obj-libc-test),\
	$(deps-libc-test),\
	libc/test,\
))

