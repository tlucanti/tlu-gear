cmake_minimum_required(VERSION 3.21)
project(language C)

set(CMAKE_C_STANDARD 23)

include_directories(inc)
include_directories(TLUlib/inc)
include_directories(.)

add_executable(language
        main.c
        src/TLUobjstack.c
        src/TLUnum.c
        src/TLUbuiltin.c
        src/TLUglobals.c
        src/TLUstr.c
        src/TLUoperators.c
        TLUlib/src/TLUnistd.c
        TLUlib/src/TLUstring.c
        TLUlib/src/TLUlexical.c
        TLUlib/src/TLUmemory.c
        )
