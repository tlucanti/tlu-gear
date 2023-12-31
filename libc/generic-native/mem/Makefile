
obj-libc	=
obj-libc	+= mem/memchr.o
obj-libc	+= mem/memcmp.o
obj-libc	+= mem/memcpy.o
obj-libc	+= mem/memeq.o
obj-libc	+= mem/memmove.o
obj-libc	+= mem/memnchr.o
obj-libc	+= mem/memset.o
obj-libc	+= mem/memzero.o

obj-libc	+= char/isalnum.o
obj-libc	+= char/isalpha.o
obj-libc	+= char/isdigit.o
obj-libc	+= char/ishex.o
obj-libc	+= char/islower.o
obj-libc	+= char/isprint.o
obj-libc	+= char/ispunct.o
obj-libc	+= char/isspace.o
obj-libc	+= char/isupper.o
obj-libc	+= char/tolower.o
obj-libc	+= char/toupper.o

obj-libc	+= string/sstartswith.o
obj-libc	+= string/strchr.o
obj-libc	+= string/strcmp.o
obj-libc	+= string/streq.o
obj-libc	+= string/strlen.o
obj-libc	+= string/strrchr.o

obj-libc	+= lexical/numtos_base.o
obj-libc	+= lexical/numtos.o
obj-libc	+= lexical/unumtos_base.o
obj-libc	+= lexical/unumtos.o

deps-libc	=

target-libc	= build/libc.a

$(eval $(call build_library,\
	$(target-libc),\
	$(obj-libc),\
	$(deps-libc),\
	libc/$(CONFIG_LIBC_TYPE),\
))

