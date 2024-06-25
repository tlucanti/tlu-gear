
obj-libc-bench	=
obj-libc-bench	+= libc_bench.o

deps-libc-bench	= $(target-libmem) $(target-libchar) $(target-liblexical) $(target-libstring) $(target-libbench) $(target-core)

target-libc-bench= build/libc_benchmark.elf

$(eval $(call build_executable,\
	$(target-libc-bench),\
	$(obj-libc-bench),\
	$(deps-libc-bench),\
	libc/perf,\
))

