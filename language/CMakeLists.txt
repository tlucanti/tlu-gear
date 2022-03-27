cmake_minimum_required(VERSION 3.21)
project(language C)

set(CMAKE_C_STANDARD 23)

include_directories(inc)
include_directories(.)

add_executable(language
        main.c
        src/TLUobjstack.c
        src/TLUnum.c
        src/TLUbuiltin.c
        src/TLUstr.c
        src/TLUoperators.c
        src/TLUmemory.c
        )
