
#ifndef _CORE_VARIADIC_H_
#define _CORE_VARIADIC_H_

#ifndef __VA_SIZE__
# define __VA_SIZE__(...) (__va_size(0, ##__VA_ARGS__, __va_seq()) - 1)
# define __va_size(...) __va_size_n(__VA_ARGS__)
# define __va_size_n(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, n, ...) n
# define __va_seq() 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#endif

# define _BR ()
# define _EX(...) _EX1(_EX1(_EX1(_EX1(__VA_ARGS__))))
# define _EX1(...) _EX2(_EX2(_EX2(_EX2(__VA_ARGS__))))
# define _EX2(...) __VA_ARGS__
# define __TP_SWITCH() _TP_SWITCH
# define _TP_SWITCH(a1, ...) typeof(a1) __VA_OPT__(, __TP_SWITCH _BR (__VA_ARGS__))

# define TYPE_SWITCH(...) _EX((void (*)(_TP_SWITCH(__VA_ARGS__)))0)
# define TYPE_CASE(...) void (*)(__VA_ARGS__)

#endif /* _CORE_VARIADIC_H_ */

