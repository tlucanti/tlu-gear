
obj-libio-test		=
obj-libio-test		+= libio_test.o
obj-libio-test		+= libio_test_utils.o
obj-libio-test		+= ../libc_test_utils.o

deps-libio-test		= $(target-libio) $(target-utest)

target-libio-test	= build/libio_unittest.elf

$(eval $(call build_executable,\
	$(target-libio-test),\
	$(obj-libio-test),\
	$(deps-libio-test),\
	libc/test/io,\
))

