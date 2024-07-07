
obj-cvector-test	=

obj-cvector-test	+= cvector_test.o

deps-cvector-test	= $(target-libmem) $(target-utest)

target-cvector-test	= build/cvector_unittest.elf

$(eval $(call build_executable,\
	$(target-cvector-test),\
	$(obj-cvector-test),\
	$(deps-cvector-test),\
	container/cvector/test,\
))

