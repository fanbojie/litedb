#ifndef LITEBASE_MACRO_H
#define LITEBASE_MACRO_H

#define DELETE_PTR(ptr)\
    delete ptr;\
    ptr = NULL;

#define  SAFE_COPY_PTR(str, ptr)\
    do                          \ 
    {                           \
        if (ptr != NULL)        \
        {                       \
            str = ptr;          \
        }                       \
    } while (0);
#endif