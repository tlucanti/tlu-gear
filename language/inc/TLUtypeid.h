
#ifndef TLU_TYPEID_H
# define TLU_TYPEID_H

typedef enum _TLUtypeid
{
    _TLUOBJ_END_TYPEID,
    TLUOBJ_STR_TYPEID,
    TLUOBJ_NUM_TYPEID,
    TLUOBJ_NUM_LONG_TYPEID,
    TLUOBJ_EXCEPTION_TYPEID,
    TLU_OBJ_CNT
} TLUtypeid;

const char *TLUtypenames[] =
{
    [_TLUOBJ_END_TYPEID]    = "<internal type 'END'>",
    [TLUOBJ_NUM_TYPEID]     = "'num'",
    [TLUOBJ_NUM_LONG_TYPEID]= "'num'",
    [TLUOBJ_STR_TYPEID]     = "'str'"
};

# define IS_END(__obj)          ((__obj).typeid == _TLUOBJ_END_TYPEID)
# define IS_STR(__obj)          ((__obj).typeid == TLUOBJ_STR_TYPEID)
# define IS_SHORT_NUM(__obj)    ((__obj).typeid == TLUOBJ_NUM_TYPEID)
# define IS_LONG_NUM(__obj)     ((__obj).typeid == TLUOBJ_NUM_LONG_TYPEID)
# define IS_NUM(__obj)          (IS_SHORT_NUM(__obj) || IS_LONG_NUM(__obj))
# define IS_EXCEPTION(__ob)     ((__obj).typeid == TLUOBJ_EXCEPTION_TYPEID)


#endif /*ATLU_TYPEID_H */
