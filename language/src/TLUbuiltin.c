/*
* @Author: tlucanti
* @Date:   2022-03-27 16:27:59
* @Last Modified by:   tlucanti
* @Last Modified time: 2022-03-27 23:28:30
*/

#include <TLUobject.h>
#include <TLUbuiltin.h>
#include <TLUstr.h>
#include <TLUnum.h>
#include <TLUnistd.h>
#include <TLUexception.h>
#include <TLUlexical.h>

TLUobject _TLU_sum(size_t argc, TLUobject *argv)
{
    if (argc == 0)
        throw(TypeError(TLUstr("function sum() takes at least 1 argument (0 given)")));
    TLUobject counter = copy(argv[0]);
    while (argc--) {
        _TLU_operator_iadd_vec[counter.typeid][argv->typeid](counter, *argv);
        ++argv;
    }
    return counter;
}

TLUobject _TLU_print(size_t argc, TLUobject *argv)
{
    intmax_t cnt = 0;

    while (argc)
    {
        _TLUstr *arg_str = _TLU_operator_str_vec[argv->typeid](*argv).object;
        cnt += _TLUwrite(1, arg_str->buf, arg_str->size);
        ++argv;
        if (argv->typeid == _TLUOBJ_END_TYPEID)
            break;
        cnt += _TLUwrite(1, " ", 1);
    }
    cnt += _TLUwrite(1, "\n", 1);
    return TLUnum(cnt);
}

TLUobject _TLU_copy(TLUobject obj)
{
    return _TLU_operator_copy_vec[obj.typeid](obj);
}

__WUR
TLUobject _TLU_num(size_t argc, TLUobject *argv)
{
    intmax_t            base = 10;
    lexical_cast_errors errors;

    if (argc == 0)
        return TLUnum(0);
    if (argc > 2)
        throw(TypeError(format(TLUstr("function num() takes at most 2 arguments {} given"), TLUnum(argc))));
    else if (argc == 2)
    {
        ASSERT_NUM(argv[1]);
        base = _GET_NUM_NUM(argv[1]);
    }
    if (base < 2 || base > 36)
        throw(ValueError(TLUstr("num() base should be in range [2:36]")));
    ASSERT_STR(argv[1]);
    _TLUs2num(_GET_STR_BUF(argv[0]), &errors, (int)base);
    if (errors)
        throw(ValueError(something));
}
