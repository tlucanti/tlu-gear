
obj-liblexical-test	=
obj-liblexical-test	+= liblexical_test.o
obj-liblexical-test	+= liblexical_test_utils.o
obj-liblexical-test	+= ../libc_test_utils.o

deps-liblexical-test	= $(target-liblexical) $(target-utest)

target-liblexical-test	= build/liblexical_unittest.elf

$(eval $(call build_executable,\
	$(target-liblexical-test),\
	$(obj-liblexical-test),\
	$(deps-liblexical-test),\
	libc/test/lexical,\
))

