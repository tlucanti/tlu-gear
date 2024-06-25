
obj-cvector-container-test	=
obj-cvector-container-test	+= cvector_test.o

deps-cvector-container-test	= $(target-cvector-container)

target-cvector-container-test	= build/cvector_test.elf

$(eval $(call build_executable,\
	$(target-cvector-container-test),\
	$(obj-cvector-container-test),\
	$(deps-cvector-container-test),\
	container/cvector/test\
))

