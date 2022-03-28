
#ifndef TLU_TYPEID_H
# define TLU_TYPEID_H

typedef enum _TLUtypeid
{
    _TLUOBJ_END_TYPEID,
    TLUOBJ_STR_TYPEID,
    TLUOBJ_NUM_TYPEID,
    TLUOBJ_NUM_LONG_TYPEID,
    TLU_OBJ_CNT
} TLUtypeid;

const char *TLUtypenames[] =
{
    [_TLUOBJ_END_TYPEID]    = "<internal type 'END'>",
    [TLUOBJ_NUM_TYPEID]     = "'num'",
    [TLUOBJ_NUM_LONG_TYPEID]= "'num'",
    [TLUOBJ_STR_TYPEID]     = "'str'"
};


#endif /*ATLU_TYPEID_H */
