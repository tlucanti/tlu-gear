/*
* @Author: tlucanti
* @Date:   2022-03-27 17:31:50
* @Last Modified by:   tlucanti
* @Last Modified time: 2022-03-27 17:35:36
*/

#include <TLUmemory.h>
#include <TLUnistd.h>

void *_TLUallocator(size_t size)
{
    void *ret = malloc(size);
    __alloc_log("allocated: %p\n", ret);
    if (!ret)
    {
        _TLUwrite(2, "out of memory\n", 14);
        exit(1);
    }
    return ret;
}

void _TLUdeallocator(void *ptr)
{
    __alloc_log("deallocating %p\n", ptr);
    free(ptr);
}
