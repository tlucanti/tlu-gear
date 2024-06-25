
obj-libchar-test	=
obj-libchar-test	+= libchar_test.o
obj-libchar-test	+= libchar_test_utils.o
obj-libchar-test	+= ../libc_test_utils.o

deps-libchar-test	= $(target-libchar) $(target-utest)

target-libchar-test	= build/libchar_unittest.elf

$(eval $(call build_executable,\
	$(target-libchar-test),\
	$(obj-libchar-test),\
	$(deps-libchar-test),\
	libc/test/char,\
))

