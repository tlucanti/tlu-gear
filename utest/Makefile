
obj-utest	=
obj-utest	+= utest.o utils.o

deps-utest	= $(target-libcore)

target-utest	= build/libutest.a

$(eval $(call build_library,\
	$(target-utest),\
	$(obj-utest),\
	$(deps-utest),\
	utest,\
))

