cmake_minimum_required(VERSION 3.20)

project(libTLU C)
set(CMAKE_C_STANDARD 11)
set (CMAKE_VERBOSE_MAKEFILE OFF)
set ( CMAKE_C_FLAGS "-mavx512vl")
add_executable(libTLU main.c src/TLUmemset_xmm.c)

#add_executable(memset  test/color.h test/test.h inc/libTLU.h
#	test/test_all_memset.c src/TLUmemset.c)

#add_executable(test test.c test/test.h)

