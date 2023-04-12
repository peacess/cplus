#include <cstdio>
#include "static_.h"
#include "inline_.h"

static void static_f()
{
    static int count = 0;
    count++;
    printf("static: %d\n", count);
}

static void static_call_inline(){
    inline_f();
}