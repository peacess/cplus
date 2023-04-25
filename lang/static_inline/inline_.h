#ifndef lang_static_inline_inline_h
#define lang_static_inline_inline_h

#include <cstdio>

/// @brief inline函数的实现如果不在头文件中的话，需要 include inline函数的实现
/// 保证同一个inline函数是一样的， 不然会产生不一至的行为，所以建议inline函数实现体在头文件中
inline void inline_f()
{
    static int count = 0;
    count++;
    printf("inline:　%d\n", count);
}

#endif