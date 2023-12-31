
obj-libchar	=

obj-libchar	+= isalnum.o
obj-libchar	+= isalpha.o
obj-libchar	+= isdigit.o
obj-libchar	+= ishex.o
obj-libchar	+= islower.o
obj-libchar	+= isprint.o
obj-libchar	+= ispunct.o
obj-libchar	+= isspace.o
obj-libchar	+= isupper.o
obj-libchar	+= tolower.o
obj-libchar	+= toupper.o

deps-libchar	=

target-libchar	= build/libchar.a

$(eval $(call build_library,\
	$(target-libchar),\
	$(obj-libchar),\
	$(deps-libchar),\
	libc/$(CONFIG_LIBC_TYPE)/char,\
))

