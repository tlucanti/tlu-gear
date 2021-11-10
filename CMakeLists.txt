cmake_minimum_required(VERSION 3.20)
project(libTLU C)

set(CMAKE_C_STANDARD 11)

add_executable(memset  test/color.h test/test.h inc/libTLU.h
	test/test_memset.c src/TLUmemset.c)

#add_executable(test test.c test/test.h)
