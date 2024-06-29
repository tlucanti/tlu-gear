
#ifndef CORE_TYPES_H
#define CORE_TYPES_H

typedef _Bool bool;
typedef unsigned int uint;

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

#define true (bool)1
#define false (bool)0
#define NULL (void *)0UL

#define INT8_MIN		(int8)(-128)
#define INT16_MIN		(int16)(-32768)
#define INT32_MIN		(int32)(-2147483648)
#define INT64_MIN		(int64)(-9223372036854775808L)

#define INT8_MAX		(int8)(127)
#define INT16_MAX		(int16)(32767)
#define INT32_MAX		(int32)(2147483647)
#define INT64_MAX		(int64)(9223372036854775807L)

#define UINT8_MAX		(uint8)(255U)
#define UINT16_MAX		(uint16)(65535U)
#define UINT32_MAX		(uint32)(4294967295U)
#define UINT64_MAX		(uint64)(18446744073709551615UL)

#endif /* CORE_TYPES_H */

