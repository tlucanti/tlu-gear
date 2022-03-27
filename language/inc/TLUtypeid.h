
#ifndef TLU_TYPEID_H
# define TLU_TYPEID_H

typedef enum _TLUtypeid
{
    _TLUOBJ_END_TYPEID      = 0b000,
    TLUOBJ_STR_TYPEID       = 0b001,
    TLUOBJ_NUM_TYPEID       = 0b010,
    TLUOBJ_NUM_LONG_TYPEID  = 0b011,
    TLU_OBJ_CNT             = 4
} TLUtypeid;

const char *TLUtypenames[] =
{
    [_TLUOBJ_END_TYPEID]    = "<internal type 'END'>",
    [TLUOBJ_NUM_TYPEID]     = "'num'",
    [TLUOBJ_STR_TYPEID]     = "'str'"
};


#endif /*ATLU_TYPEID_H */
