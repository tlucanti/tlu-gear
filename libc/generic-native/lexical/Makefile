
obj-liblexical	=
obj-liblexical	+= numtos_base.o
obj-liblexical	+= numtos.o
obj-liblexical	+= unumtos_base.o
obj-liblexical	+= unumtos.o

deps-liblexical	=

target-liblexical= build/liblexical.a

$(eval $(call build_library,\
	$(target-liblexical),\
	$(obj-liblexical),\
	$(deps-liblexical),\
	libc/$(CONFIG_LIBC_TYPE)/lexical,\
))

