#include <cstdio>

static inline void static_inline_f(){
    static int count = 0;
    count++;
    printf("static_inline:　%d\n", count);
}

