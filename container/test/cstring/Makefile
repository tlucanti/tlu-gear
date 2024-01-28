
obj-cstring-container-test	=
obj-cstring-container-test	+= cstring_test.o

deps-cstring-container-test	= $(target-cstring-container)

target-cstring-container-test	= build/cstring_test.elf

$(eval $(call build_executable,\
	$(target-cstring-container-test),\
	$(obj-cstring-container-test),\
	$(deps-cstring-container-test),\
	container/test/cstring\
))

