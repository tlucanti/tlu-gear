/*
* @Author: tlucanti
* @Date:   2022-03-27 16:27:59
* @Last Modified by:   tlucanti
* @Last Modified time: 2022-03-27 23:28:30
*/

#include "../inc/TLUobject.h"
#include "../inc/TLUbuiltin.h"

TLUobject   _TLU_sum(size_t argc, TLUobject *argv)
{
    if (argc == 0)
        throw (TypeError("function sum() takes at least 1 argument (0 given)"));
    TLUobject counter = copy(args[0]);
    while (argc--)
    {
        _TLU_operator_iadd_vec[counter.typeid][args->typeid](counter, *args);
        ++args;
    }
    return counter;
}

TLUobject _TLU_print(size_t argc, TLUobject *argv)
{
    int cnt = 0;
    
    while (argc)
    {

       	_TLUstr arg_str = _TLU_operator_str_vec[args->typeid](*args).object;
        cnt += _TLUwrite(arg_str->buf, arg_str->size);
        ++args;
        if (args->typeid == _TLUOBJ_END_TYPEID)
            break ;
        cnt += _TLUwrite(" ", 1);
    }
    cnt += _TLUwrite(1, "\n", 1);
    return num(cnt);
}

TLUobject _TLU_copy(TLUobject obj)
{
    return _TLU_operator_copy_vec[obj->typeid](obj);
}

__WUR
TLUobject   _TLU_num(size_t argc, TLUobject *argv)
{
    int base = 10;
    int argnum = 

    if (args[0] == _TLUOBJ_END_TYPEID)
        return TLUnum(0);
    if (args[1] != _TLUOBJ_END_TYPEID)
    {
        if (args[2] != _TLUOBJ_END_TYPEID)
            throw(TypeError(format("function num() takes at most 2 arguments {} given", ));
    }
}
