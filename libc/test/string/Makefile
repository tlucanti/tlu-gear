
obj-libstring-test	=
obj-libstring-test	+= strlen_test.o

obj-libstring-test	+= libstring_test.o

deps-libstring-test	= $(target-libstring) $(target-utest)

target-libstring-test	= build/libstring_unittest.elf

$(eval $(call build_executable,\
	$(target-libstring-test),\
	$(obj-libstring-test),\
	$(deps-libstring-test),\
	libc/test/string,\
))

